"""
Builds /Game/Effects/M_GlitchPresence_Master — the master material the
UGlitchPresenceComponent drives via GlitchPhase + GlitchSeed scalar parameters.

Usage (inside the UE editor):
    1. Enable the "Python Editor Script Plugin" in Edit > Plugins (restart once).
    2. Window > Output Log → keep the bottom dropdown on "Cmd".
    3. Run:  py C:/Users/alexx/Documents/LLM-NPC/Content/Python/build_glitch_material.py

Exposes these scalar parameters (tweakable per Material Instance):
    GlitchPhase     — driven by component, 0 visible → 1 hidden
    GlitchSeed      — driven by component, randomises pattern
    GlitchIntensity — overall strength multiplier (default 1)
    DisplaceAmount  — max WorldPositionOffset in cm (default 15)
    ChromaOffset    — chromatic aberration UV shift during transition (default 0.012)
    GlowIntensity   — emissive edge glow strength (default 3)

Plus one texture parameter:
    BaseColorTex    — the object's albedo
"""

import unreal
import math

PACKAGE_PATH = "/Game/Effects"
MATERIAL_NAME = "M_GlitchPresence_Master"
ASSET_PATH = f"{PACKAGE_PATH}/{MATERIAL_NAME}"

mel = unreal.MaterialEditingLibrary
eal = unreal.EditorAssetLibrary
tools = unreal.AssetToolsHelpers.get_asset_tools()


def ensure_folder(path):
    if not eal.does_directory_exist(path):
        eal.make_directory(path)


def make_scalar(mat, name, default, x, y):
    node = mel.create_material_expression(
        mat, unreal.MaterialExpressionScalarParameter, x, y)
    node.set_editor_property("parameter_name", name)
    node.set_editor_property("default_value", default)
    return node


def make_const(mat, value, x, y):
    node = mel.create_material_expression(
        mat, unreal.MaterialExpressionConstant, x, y)
    node.set_editor_property("r", value)
    return node


def make_vec3(mat, r, g, b, x, y):
    node = mel.create_material_expression(
        mat, unreal.MaterialExpressionConstant3Vector, x, y)
    node.set_editor_property("constant", unreal.LinearColor(r, g, b, 0.0))
    return node


def make_tex_param(mat, param_name, x, y):
    node = mel.create_material_expression(
        mat, unreal.MaterialExpressionTextureSampleParameter2D, x, y)
    node.set_editor_property("parameter_name", param_name)
    return node


def make_mask(mat, expr, r, g, b, x, y):
    node = mel.create_material_expression(
        mat, unreal.MaterialExpressionComponentMask, x, y)
    node.set_editor_property("r", r)
    node.set_editor_property("g", g)
    node.set_editor_property("b", b)
    node.set_editor_property("a", False)
    mel.connect_material_expressions(expr, "", node, "")
    return node


def build():
    ensure_folder(PACKAGE_PATH)

    if eal.does_asset_exist(ASSET_PATH):
        eal.delete_asset(ASSET_PATH)

    material = tools.create_asset(
        MATERIAL_NAME, PACKAGE_PATH, unreal.Material, unreal.MaterialFactoryNew())

    material.set_editor_property("blend_mode", unreal.BlendMode.BLEND_MASKED)
    material.set_editor_property("opacity_mask_clip_value", 0.5)

    # ---------- Parameters ----------
    glitch_phase     = make_scalar(material, "GlitchPhase",       0.0,   -1800,    0)
    glitch_seed      = make_scalar(material, "GlitchSeed",        0.0,   -1800,  160)
    glitch_intensity = make_scalar(material, "GlitchIntensity",   1.0,   -1800,  320)
    displace_amount  = make_scalar(material, "DisplaceAmount",   15.0,   -1800,  480)
    chroma_offset    = make_scalar(material, "ChromaOffset",      0.035, -1800,  640)
    glow_intensity   = make_scalar(material, "GlowIntensity",     6.0,   -1800,  800)

    # ---------- Visibility = 1 - GlitchPhase ----------
    visibility = mel.create_material_expression(
        material, unreal.MaterialExpressionOneMinus, -1500, 0)
    mel.connect_material_expressions(glitch_phase, "", visibility, "")

    # ---------- Noise (dissolve mask) ----------
    noise = mel.create_material_expression(
        material, unreal.MaterialExpressionNoise, -1500, 160)
    noise.set_editor_property("scale", 4.0)
    noise.set_editor_property("output_min", 0.0)
    noise.set_editor_property("output_max", 1.0)

    # ---------- OpacityMask = Noise - Visibility ----------
    mask_sub = mel.create_material_expression(
        material, unreal.MaterialExpressionSubtract, -1200, 80)
    mel.connect_material_expressions(noise, "", mask_sub, "A")
    mel.connect_material_expressions(visibility, "", mask_sub, "B")
    mel.connect_material_property(mask_sub, "", unreal.MaterialProperty.MP_OPACITY_MASK)

    # ---------- Envelope = sin(GlitchPhase * pi) ----------
    pi_const = make_const(material, math.pi, -1500, 580)
    phase_pi = mel.create_material_expression(
        material, unreal.MaterialExpressionMultiply, -1300, 500)
    mel.connect_material_expressions(glitch_phase, "", phase_pi, "A")
    mel.connect_material_expressions(pi_const, "", phase_pi, "B")

    envelope = mel.create_material_expression(
        material, unreal.MaterialExpressionSine, -1100, 500)
    mel.connect_material_expressions(phase_pi, "", envelope, "")

    # ---------- Edge glow = (1 - |mask_sub|) ^ 15 * GlitchIntensity * GlowIntensity * envelope ----------
    edge_abs = mel.create_material_expression(
        material, unreal.MaterialExpressionAbs, -1000, 220)
    mel.connect_material_expressions(mask_sub, "", edge_abs, "")

    edge_inv = mel.create_material_expression(
        material, unreal.MaterialExpressionOneMinus, -820, 220)
    mel.connect_material_expressions(edge_abs, "", edge_inv, "")

    edge_pow_exp = make_const(material, 15.0, -820, 360)
    edge_pow = mel.create_material_expression(
        material, unreal.MaterialExpressionPower, -640, 220)
    mel.connect_material_expressions(edge_inv, "", edge_pow, "Base")
    mel.connect_material_expressions(edge_pow_exp, "", edge_pow, "Exp")

    # Cyan-magenta lerp driven by GlitchSeed → color varies per cycle.
    color_a = make_vec3(material, 0.2, 0.9, 1.0,  -640, 380)   # cyan
    color_b = make_vec3(material, 1.0, 0.3, 0.9,  -640, 500)   # magenta
    color_lerp = mel.create_material_expression(
        material, unreal.MaterialExpressionLinearInterpolate, -440, 380)
    mel.connect_material_expressions(color_a, "", color_lerp, "A")
    mel.connect_material_expressions(color_b, "", color_lerp, "B")

    seed_frac = mel.create_material_expression(
        material, unreal.MaterialExpressionFrac, -640, 620)
    mel.connect_material_expressions(glitch_seed, "", seed_frac, "")
    mel.connect_material_expressions(seed_frac, "", color_lerp, "Alpha")

    em_mul_color = mel.create_material_expression(
        material, unreal.MaterialExpressionMultiply, -220, 220)
    mel.connect_material_expressions(edge_pow, "", em_mul_color, "A")
    mel.connect_material_expressions(color_lerp, "", em_mul_color, "B")

    em_mul_glow = mel.create_material_expression(
        material, unreal.MaterialExpressionMultiply, -40, 220)
    mel.connect_material_expressions(em_mul_color, "", em_mul_glow, "A")
    mel.connect_material_expressions(glow_intensity, "", em_mul_glow, "B")

    em_mul_int = mel.create_material_expression(
        material, unreal.MaterialExpressionMultiply, 140, 220)
    mel.connect_material_expressions(em_mul_glow, "", em_mul_int, "A")
    mel.connect_material_expressions(glitch_intensity, "", em_mul_int, "B")

    em_final = mel.create_material_expression(
        material, unreal.MaterialExpressionMultiply, 320, 220)
    mel.connect_material_expressions(em_mul_int, "", em_final, "A")
    mel.connect_material_expressions(envelope, "", em_final, "B")

    mel.connect_material_property(em_final, "", unreal.MaterialProperty.MP_EMISSIVE_COLOR)

    # ---------- WPO: 3D noise × envelope × DisplaceAmount along world X ----------
    wpo_noise = mel.create_material_expression(
        material, unreal.MaterialExpressionNoise, -1300, 760)
    wpo_noise.set_editor_property("scale", 0.5)
    wpo_noise.set_editor_property("output_min", -1.0)
    wpo_noise.set_editor_property("output_max", 1.0)

    wpo_mul_env = mel.create_material_expression(
        material, unreal.MaterialExpressionMultiply, -1000, 700)
    mel.connect_material_expressions(wpo_noise, "", wpo_mul_env, "A")
    mel.connect_material_expressions(envelope, "", wpo_mul_env, "B")

    wpo_mul_amount = mel.create_material_expression(
        material, unreal.MaterialExpressionMultiply, -800, 700)
    mel.connect_material_expressions(wpo_mul_env, "", wpo_mul_amount, "A")
    mel.connect_material_expressions(displace_amount, "", wpo_mul_amount, "B")

    x_axis = make_vec3(material, 1.0, 0.0, 0.0, -800, 840)
    wpo_vec = mel.create_material_expression(
        material, unreal.MaterialExpressionMultiply, -600, 700)
    mel.connect_material_expressions(wpo_mul_amount, "", wpo_vec, "A")
    mel.connect_material_expressions(x_axis, "", wpo_vec, "B")

    mel.connect_material_property(
        wpo_vec, "", unreal.MaterialProperty.MP_WORLD_POSITION_OFFSET)

    # ---------- Chromatic aberration on BaseColor ----------
    # shift = envelope * ChromaOffset
    shift_scalar = mel.create_material_expression(
        material, unreal.MaterialExpressionMultiply, -1300, 1000)
    mel.connect_material_expressions(envelope, "", shift_scalar, "A")
    mel.connect_material_expressions(chroma_offset, "", shift_scalar, "B")

    # shiftR_vec = (shift, 0), shiftB_vec = (-shift, 0)
    zero_const = make_const(material, 0.0, -1100, 1140)
    shiftR = mel.create_material_expression(
        material, unreal.MaterialExpressionAppendVector, -1100, 1000)
    mel.connect_material_expressions(shift_scalar, "", shiftR, "A")
    mel.connect_material_expressions(zero_const, "", shiftR, "B")

    neg_shift = mel.create_material_expression(
        material, unreal.MaterialExpressionMultiply, -1100, 1200)
    mel.connect_material_expressions(shift_scalar, "", neg_shift, "A")
    neg_one = make_const(material, -1.0, -1300, 1280)
    mel.connect_material_expressions(neg_one, "", neg_shift, "B")

    shiftB = mel.create_material_expression(
        material, unreal.MaterialExpressionAppendVector, -900, 1200)
    mel.connect_material_expressions(neg_shift, "", shiftB, "A")
    mel.connect_material_expressions(zero_const, "", shiftB, "B")

    # UV_R = UV + shiftR, UV_G = UV, UV_B = UV + shiftB
    uv = mel.create_material_expression(
        material, unreal.MaterialExpressionTextureCoordinate, -1300, 1400)

    uv_r = mel.create_material_expression(
        material, unreal.MaterialExpressionAdd, -700, 1000)
    mel.connect_material_expressions(uv, "", uv_r, "A")
    mel.connect_material_expressions(shiftR, "", uv_r, "B")

    uv_b = mel.create_material_expression(
        material, unreal.MaterialExpressionAdd, -700, 1200)
    mel.connect_material_expressions(uv, "", uv_b, "A")
    mel.connect_material_expressions(shiftB, "", uv_b, "B")

    # Three samples of BaseColorTex (shared parameter → single slot in instance UI)
    sample_r = make_tex_param(material, "BaseColorTex", -500, 1000)
    sample_g = make_tex_param(material, "BaseColorTex", -500, 1200)
    sample_b = make_tex_param(material, "BaseColorTex", -500, 1400)

    mel.connect_material_expressions(uv_r, "", sample_r, "Coordinates")
    mel.connect_material_expressions(uv, "", sample_g, "Coordinates")
    mel.connect_material_expressions(uv_b, "", sample_b, "Coordinates")

    # Extract per-channel and re-assemble
    r_only = make_mask(material, sample_r, True,  False, False, -200, 1000)
    g_only = make_mask(material, sample_g, False, True,  False, -200, 1200)
    b_only = make_mask(material, sample_b, False, False, True,  -200, 1400)

    rg = mel.create_material_expression(
        material, unreal.MaterialExpressionAppendVector, 0, 1100)
    mel.connect_material_expressions(r_only, "", rg, "A")
    mel.connect_material_expressions(g_only, "", rg, "B")

    rgb = mel.create_material_expression(
        material, unreal.MaterialExpressionAppendVector, 200, 1200)
    mel.connect_material_expressions(rg, "", rgb, "A")
    mel.connect_material_expressions(b_only, "", rgb, "B")

    mel.connect_material_property(rgb, "", unreal.MaterialProperty.MP_BASE_COLOR)

    # ---------- Compile + save ----------
    mel.recompile_material(material)
    eal.save_asset(ASSET_PATH)
    unreal.log(f"Built {ASSET_PATH}")


try:
    build()
except Exception as exc:
    import traceback
    unreal.log_error(f"build_glitch_material FAILED: {exc}")
    unreal.log_error(traceback.format_exc())
