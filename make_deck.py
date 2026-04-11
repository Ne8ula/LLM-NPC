"""
Generate LLM-NPC slide deck as a PowerPoint file.
Run: py make_deck.py
Output: slide-deck.pptx
"""

from pptx import Presentation
from pptx.util import Inches, Pt, Emu
from pptx.dml.color import RGBColor
from pptx.enum.text import PP_ALIGN
from pptx.util import Inches, Pt
from pptx.oxml.ns import qn
from pptx.oxml import parse_xml
from lxml import etree
import copy

# ── Palette ────────────────────────────────────────────────────────────────
BG      = RGBColor(0x0d, 0x11, 0x17)
SURFACE = RGBColor(0x16, 0x1b, 0x22)
SURF2   = RGBColor(0x21, 0x26, 0x2d)
BORDER  = RGBColor(0x30, 0x36, 0x3d)
TEXT    = RGBColor(0xe6, 0xed, 0xf3)
MUTED   = RGBColor(0x8b, 0x94, 0x9e)
BLUE    = RGBColor(0x58, 0xa6, 0xff)
GREEN   = RGBColor(0x3f, 0xb9, 0x50)
AMBER   = RGBColor(0xd2, 0x99, 0x22)
PURPLE  = RGBColor(0xbc, 0x8c, 0xff)
RED     = RGBColor(0xf8, 0x51, 0x49)
TEAL    = RGBColor(0x39, 0xd3, 0x53)
ACCENT  = RGBColor(0x1f, 0x6f, 0xeb)

# Slide dimensions (widescreen 16:9)
W = Inches(13.33)
H = Inches(7.5)

prs = Presentation()
prs.slide_width  = W
prs.slide_height = H

blank_layout = prs.slide_layouts[6]  # completely blank


# ── Helpers ────────────────────────────────────────────────────────────────

def add_slide():
    slide = prs.slides.add_slide(blank_layout)
    # Dark background
    bg = slide.background
    fill = bg.fill
    fill.solid()
    fill.fore_color.rgb = BG
    return slide


def rect(slide, x, y, w, h, fill_color=None, border_color=None, border_width=Pt(0.75), radius=None):
    """Add a filled rectangle (optionally rounded)."""
    shape = slide.shapes.add_shape(
        1,  # MSO_SHAPE_TYPE.RECTANGLE = 1  → pptx auto-maps to rounded if radius given
        x, y, w, h
    )
    shape.line.width = border_width
    if fill_color:
        shape.fill.solid()
        shape.fill.fore_color.rgb = fill_color
    else:
        shape.fill.background()
    if border_color:
        shape.line.color.rgb = border_color
    else:
        shape.line.fill.background()
    # Rounded corners via XML
    if radius is not None:
        sp = shape._element
        prstGeom = sp.find(qn('p:spPr')).find(qn('a:prstGeom'))
        if prstGeom is not None:
            prstGeom.set('prst', 'roundRect')
            avLst = prstGeom.find(qn('a:avLst'))
            if avLst is None:
                avLst = etree.SubElement(prstGeom, qn('a:avLst'))
            else:
                avLst.clear()
            gd = etree.SubElement(avLst, qn('a:gd'))
            gd.set('name', 'adj')
            gd.set('fmla', f'val {radius}')
    return shape


def txt(slide, text, x, y, w, h,
        size=Pt(11), bold=False, color=TEXT, align=PP_ALIGN.LEFT,
        wrap=True, italic=False):
    """Add a text box."""
    tb = slide.shapes.add_textbox(x, y, w, h)
    tf = tb.text_frame
    tf.word_wrap = wrap
    p = tf.paragraphs[0]
    p.alignment = align
    run = p.add_run()
    run.text = text
    run.font.size = size
    run.font.bold = bold
    run.font.italic = italic
    run.font.color.rgb = color
    return tb


def txt_box(slide, lines, x, y, w, h,
            bg=SURFACE, border=BORDER, pad=Inches(0.12),
            title=None, title_color=BLUE):
    """Card with optional title + bullet lines."""
    rect(slide, x, y, w, h, fill_color=bg, border_color=border, radius=20000)
    cy = y + pad
    if title:
        txt(slide, title, x + pad, cy, w - pad*2, Pt(14), size=Pt(10), bold=True, color=title_color)
        cy += Inches(0.22)
    for line in lines:
        color = line[1] if isinstance(line, tuple) else TEXT
        text  = line[0] if isinstance(line, tuple) else line
        tb = txt(slide, text, x + pad, cy, w - pad*2, Inches(0.2), size=Pt(9), color=color)
        cy += Inches(0.185)
    return cy


def section_header(slide, title, subtitle=None):
    """Slide header bar."""
    rect(slide, 0, 0, W, Inches(0.58), fill_color=SURFACE, border_color=None)
    # bottom border line
    rect(slide, 0, Inches(0.58), W, Pt(1), fill_color=BORDER, border_color=None)
    txt(slide, title, Inches(0.45), Inches(0.1), Inches(10), Inches(0.4),
        size=Pt(16), bold=True, color=BLUE)
    if subtitle:
        txt(slide, subtitle, Inches(0.45), Inches(0.34), Inches(10), Inches(0.22),
            size=Pt(9), color=MUTED)


def chip(slide, text, x, y, color):
    """Pill-shaped chip."""
    w = Inches(len(text) * 0.085 + 0.25)
    h = Inches(0.22)
    r = rect(slide, x, y, w, h, fill_color=None, border_color=color, radius=50000)
    r.fill.background()
    txt(slide, text, x, y, w, h, size=Pt(8), bold=True, color=color, align=PP_ALIGN.CENTER)
    return w


def flow_box(slide, text, x, y, w, h, fill, border, text_color=TEXT):
    rect(slide, x, y, w, h, fill_color=fill, border_color=border, radius=15000)
    txt(slide, text, x + Inches(0.06), y + Inches(0.03), w - Inches(0.12), h - Inches(0.06),
        size=Pt(8.5), color=text_color, wrap=True)


def arrow_right(slide, x, y):
    txt(slide, "→", x, y - Inches(0.05), Inches(0.2), Inches(0.2), size=Pt(14), color=MUTED, align=PP_ALIGN.CENTER)


def arrow_down(slide, x, y):
    txt(slide, "↓", x - Inches(0.06), y, Inches(0.2), Inches(0.2), size=Pt(12), color=MUTED, align=PP_ALIGN.CENTER)


def make_table(slide, headers, rows, x, y, w, col_widths, row_height=Inches(0.28)):
    """Draw a table manually with rectangles and text."""
    n_cols = len(headers)
    # Header row
    cx = x
    for i, h_text in enumerate(headers):
        cw = col_widths[i]
        rect(slide, cx, y, cw, row_height, fill_color=SURF2, border_color=BORDER, border_width=Pt(0.5))
        txt(slide, h_text, cx + Inches(0.06), y + Inches(0.05), cw - Inches(0.12), row_height,
            size=Pt(8), bold=True, color=MUTED)
        cx += cw
    # Data rows
    ry = y + row_height
    for row in rows:
        cx = x
        for i, cell in enumerate(row):
            cw = col_widths[i]
            text  = cell[0] if isinstance(cell, tuple) else cell
            color = cell[1] if isinstance(cell, tuple) else TEXT
            rect(slide, cx, ry, cw, row_height, fill_color=SURFACE, border_color=BORDER, border_width=Pt(0.5))
            txt(slide, text, cx + Inches(0.06), ry + Inches(0.04), cw - Inches(0.12), row_height - Inches(0.04),
                size=Pt(8), color=color, wrap=True)
            cx += cw
        ry += row_height
    return ry


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 1 — Title & Hook
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()

# Left accent gradient band
rect(s, 0, 0, Inches(0.06), H, fill_color=BLUE, border_color=None)

# Title
txt(s, "Conversational NPCs with Real-Time AI",
    Inches(0.35), Inches(0.9), Inches(7.5), Inches(1.1),
    size=Pt(30), bold=True, color=TEXT)

txt(s, "A modular Metahuman NPC system · Unreal Engine 5.7",
    Inches(0.35), Inches(2.1), Inches(7.5), Inches(0.35),
    size=Pt(12), color=MUTED)

txt(s, "Claude LLM  ·  ElevenLabs TTS  ·  OpenAI Whisper  ·  ONNX Vision",
    Inches(0.35), Inches(2.45), Inches(8), Inches(0.3),
    size=Pt(11), color=MUTED)

# Chips
cx = Inches(0.35)
cy = Inches(3.05)
for text, color in [("Emotionally Aware", BLUE), ("Procedurally Animated", GREEN), ("Voice-Driven", PURPLE)]:
    w = chip(s, text, cx, cy, color)
    cx += w + Inches(0.15)

# Stats row
stats = [("3", "External AI APIs", BLUE), ("6", "Subsystems", GREEN), ("0", "Scripted dialogue lines", PURPLE)]
sx = Inches(0.35)
sy = Inches(3.7)
for val, label, color in stats:
    txt(s, val,   sx, sy,          Inches(1.5), Inches(0.45), size=Pt(28), bold=True, color=color)
    txt(s, label, sx, sy + Inches(0.42), Inches(1.5), Inches(0.22), size=Pt(8.5), color=MUTED)
    sx += Inches(1.9)

# Right panel — node diagram
rx = Inches(8.5)
panel_nodes = [
    ("🎙️  Voice Input",       BLUE,   Inches(4.1)),
    ("🧠  Claude + PAD",      PURPLE, Inches(5.15)),
    ("🗣️  Metahuman NPC",     GREEN,  Inches(6.2)),
]
rect(s, rx, Inches(0.2), Inches(4.6), Inches(7.1), fill_color=SURFACE, border_color=BORDER, radius=20000)
for label, color, ny in panel_nodes:
    nw, nh = Inches(2.8), Inches(0.6)
    nx = rx + (Inches(4.6) - nw) / 2
    rect(s, nx, ny, nw, nh, fill_color=None, border_color=color, radius=30000)
    txt(s, label, nx, ny, nw, nh, size=Pt(11), bold=True, color=color, align=PP_ALIGN.CENTER)
    if ny < Inches(6.2):
        arrow_down(s, nx + nw/2, ny + nh)

# Slide number label
txt(s, "1 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 2 — System Overview
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "System Overview", "What the system does end-to-end")

top = Inches(0.72)
col_w = (W - Inches(0.9)) / 3
cols = [
    ("INPUT", BLUE, [
        "🎙️  Microphone → Whisper STT",
        "⌨️   Keyboard / text fallback",
        "📷  Camera → ONNX face emotion",
        "✋  Camera → ONNX hand gestures",
    ]),
    ("BRAIN", PURPLE, [
        "Claude LLM — dialogue generation",
        "PAD Emotion State Machine",
        "Inventory unlock logic",
        "DialogueComponent — history mgmt",
    ]),
    ("OUTPUT", GREEN, [
        "🔊  ElevenLabs TTS — voice audio",
        "👄  Lip sync — viseme schedule",
        "😊  FACS face curves → RigLogic",
        "🚶  Body FK — poses + overlays",
    ]),
]

x0 = Inches(0.45)
for i, (title, color, items) in enumerate(cols):
    cx = x0 + i * (col_w + Inches(0.05))
    # Header
    rect(s, cx, top, col_w, Inches(0.38), fill_color=SURFACE, border_color=color, radius=15000)
    txt(s, title, cx, top, col_w, Inches(0.38), size=Pt(13), bold=True, color=color, align=PP_ALIGN.CENTER)
    # Items
    iy = top + Inches(0.44)
    for item in items:
        # subtle fill based on column color
        fills = {BLUE: RGBColor(0x0d, 0x1d, 0x2e), GREEN: RGBColor(0x0d, 0x1e, 0x12), PURPLE: RGBColor(0x1a, 0x14, 0x28)}
        flow_box(s, item, cx, iy, col_w, Inches(0.42), fills[color], color)
        iy += Inches(0.47)

    # Arrow between columns
    if i < 2:
        arrow_right(s, cx + col_w + Inches(0.01), top + Inches(1.1))

txt(s, "All dialogue is model-generated — zero scripted branches.",
    Inches(0.45), Inches(6.8), W - Inches(0.9), Inches(0.3),
    size=Pt(9.5), color=MUTED, italic=True, align=PP_ALIGN.CENTER)
txt(s, "2 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 3 — Subsystem Architecture
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "Subsystem Architecture", "Component ownership tree · UE4 delegates · Data assets")

# Root node
root_x = Inches(4.9)
root_y = Inches(0.8)
root_w = Inches(3.5)
root_h = Inches(0.46)
rect(s, root_x, root_y, root_w, root_h, fill_color=RGBColor(0x0d,0x1d,0x2e), border_color=BLUE, radius=15000)
txt(s, "ANPCCharacter  (root actor)", root_x, root_y, root_w, root_h,
    size=Pt(11), bold=True, color=BLUE, align=PP_ALIGN.CENTER)

# Children
children = [
    ("💬 DialogueComponent",  BLUE,   "History, routing,\nClaude API calls"),
    ("❤️  EmotionComponent",   RED,    "PAD state machine,\ndecay, transitions"),
    ("📷 VisionComponent",     GREEN,  "ONNX face + hand,\nOpenCV DNN"),
    ("🔊 Voice Pipeline",      AMBER,  "Whisper STT +\nElevenLabs TTS"),
    ("🕺 AnimComponents",      PURPLE, "Face · LipSync ·\nBody FK"),
    ("🎒 InventoryComponent",  TEAL,   "Emotion-gated\nitem unlocks"),
]

child_w = Inches(1.95)
child_h = Inches(0.75)
total_w = len(children) * child_w + (len(children)-1) * Inches(0.08)
start_x = (W - total_w) / 2
child_y = Inches(1.9)

# Vertical stem
rect(s, root_x + root_w/2 - Pt(0.5), root_y + root_h, Pt(1), child_y - (root_y + root_h), fill_color=BORDER, border_color=None)

for i, (name, color, desc) in enumerate(children):
    cx = start_x + i * (child_w + Inches(0.08))
    # horizontal line from stem to node
    mid_y = root_y + root_h + (child_y - root_y - root_h) / 2
    # connector dots handled by lines; use thin rects
    rect(s, cx + child_w/2 - Pt(0.5), mid_y, Pt(1), child_y - mid_y, fill_color=BORDER, border_color=None)
    rect(s, min(cx + child_w/2, root_x + root_w/2) - Pt(0.5),
         mid_y - Pt(0.5),
         abs(cx + child_w/2 - (root_x + root_w/2)) + Pt(1),
         Pt(1), fill_color=BORDER, border_color=None)

    fills = {BLUE: RGBColor(0x0d,0x1d,0x2e), RED: RGBColor(0x1f,0x0d,0x0d), GREEN: RGBColor(0x0d,0x1e,0x12),
             AMBER: RGBColor(0x1f,0x18,0x08), PURPLE: RGBColor(0x1a,0x14,0x28), TEAL: RGBColor(0x0c,0x1e,0x18)}
    rect(s, cx, child_y, child_w, child_h, fill_color=fills[color], border_color=color, radius=15000)
    txt(s, name, cx + Inches(0.07), child_y + Inches(0.06), child_w - Inches(0.14), Inches(0.28),
        size=Pt(9), bold=True, color=color)
    txt(s, desc, cx + Inches(0.07), child_y + Inches(0.33), child_w - Inches(0.14), Inches(0.38),
        size=Pt(8), color=MUTED, wrap=True)

# Communication & config cards
card_y = Inches(3.1)
card_h = Inches(1.35)
# Delegates card
cx1 = Inches(0.45)
cw1 = Inches(5.9)
rect(s, cx1, card_y, cw1, card_h, fill_color=SURFACE, border_color=BORDER, radius=15000)
txt(s, "Communication Pattern — UE4 Delegates (no direct coupling)", cx1+Inches(0.12), card_y+Inches(0.1), cw1-Inches(0.24), Inches(0.24), size=Pt(9.5), bold=True, color=TEXT)
delegate_lines = [
    "OnClaudeResponseReceived  →  ElevenLabs TTS · EmotionComponent · InventoryComponent",
    "OnTTSAlignmentReceived    →  NPCLipSyncComponent · NPCBodyMotionComponent",
    "OnEmotionChanged          →  MetahumanAnimComponent · InventoryComponent",
    "OnTranscriptReady         →  DialogueComponent · NPCBodyMotionComponent",
]
for j, line in enumerate(delegate_lines):
    txt(s, line, cx1+Inches(0.18), card_y+Inches(0.38)+j*Inches(0.22), cw1-Inches(0.3), Inches(0.22),
        size=Pt(8), color=MUTED)

# Data assets card
cx2 = Inches(6.65)
cw2 = Inches(6.2)
rect(s, cx2, card_y, cw2, card_h, fill_color=SURFACE, border_color=BORDER, radius=15000)
txt(s, "Configuration — Blueprint Data Assets (no C++ recompile)", cx2+Inches(0.12), card_y+Inches(0.1), cw2-Inches(0.24), Inches(0.24), size=Pt(9.5), bold=True, color=TEXT)
assets = ["NPCConfigDataAsset  — persona, voice ID, prompt, emotion defaults",
          "EmotionGraphDataAsset  — state graph nodes and transition rules",
          "InventoryDataAsset  — item catalogue and unlock conditions",
          "BlendShapeMappingDataAsset  — emotion → FACS curve weights"]
for j, a in enumerate(assets):
    txt(s, a, cx2+Inches(0.18), card_y+Inches(0.38)+j*Inches(0.22), cw2-Inches(0.3), Inches(0.22),
        size=Pt(8), color=AMBER)

txt(s, "3 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 4 — Full Data Flow
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "Full Input → Output Data Flow", "End-to-end pipeline for a single NPC turn")

bw = Inches(3.8)
bh = Inches(0.38)
bx = Inches(0.45)
by = Inches(0.78)
gap = Inches(0.14)

blue_fill   = RGBColor(0x0d,0x1d,0x2e)
purple_fill = RGBColor(0x1a,0x14,0x28)
neutral_fill = SURFACE

def fbox(slide, text, x, y, w, h, fc, bc):
    flow_box(slide, text, x, y, w, h, fc, bc)

# Step 1
fbox(s, "🎙️  Microphone  (Windows waveIn — 16kHz, 16-bit mono)", bx, by, bw*2 + Inches(0.3), bh, blue_fill, BLUE)
by += bh + gap
fbox(s, "WAV encode → OpenAI Whisper  POST /v1/audio/transcriptions", bx, by, bw*2 + Inches(0.3), bh, blue_fill, BLUE)
by += bh + gap
fbox(s, "DialogueComponent  — appends user emotion (ONNX vision) + conversation history", bx, by, bw*2 + Inches(0.3), bh, purple_fill, PURPLE)
by += bh + gap
fbox(s, "ClaudeAPISubsystem  —  POST /v1/messages  ·  rate-limited 0.5s  ·  3× exponential retry", bx, by, bw*2 + Inches(0.3), bh, purple_fill, PURPLE)
by += bh + gap
fbox(s, 'Parse JSON  →  "dialogue"  ·  "emotion_update[8]"  ·  "item_give"', bx, by, bw*2 + Inches(0.3), bh, SURFACE, BORDER)
by += bh + gap + Inches(0.05)

# Branch: 3 columns
branch_labels = [
    ("ElevenLabs TTS\n/with-timestamps", BLUE,   blue_fill,
     ["PCM audio +\nchar alignment", "USoundWaveProcedural\nplayback", "🔊 Audio + Lip Sync"]),
    ("EmotionComponent\nProcessSignal()", RED, RGBColor(0x1f,0x0d,0x0d),
     ["PAD state update", "OnEmotionChanged\nbroadcast", "😊 FACS curves\n+ Body state"]),
    ("InventoryComponent\nCheckUnlock()", AMBER, RGBColor(0x1f,0x18,0x08),
     ["Emotion threshold\n+ keyword match", "item_give check", "🎒 Item given\nto player"]),
]

bcol_w = (bw*2 + Inches(0.3) - Inches(0.2)) / 3
for i, (label, color, fill, steps) in enumerate(branch_labels):
    bx2 = bx + i * (bcol_w + Inches(0.1))
    fbox(s, label, bx2, by, bcol_w, bh + Inches(0.1), fill, color)
    sy = by + bh + Inches(0.2)
    for step in steps:
        fbox(s, step, bx2, sy, bcol_w, bh, fill, color)
        sy += bh + gap

# Legend on right
lx = Inches(9.05)
ly = Inches(0.9)
txt(s, "LEGEND", lx, ly, Inches(3.8), Inches(0.25), size=Pt(8), bold=True, color=MUTED)
legend_items = [
    ("Voice / STT / LLM", BLUE),
    ("Dialogue orchestration", PURPLE),
    ("Emotion pipeline", RED),
    ("Inventory", AMBER),
    ("Render output", GREEN),
]
for j, (label, color) in enumerate(legend_items):
    ry2 = ly + Inches(0.3) + j * Inches(0.32)
    rect(s, lx, ry2 + Inches(0.04), Inches(0.18), Inches(0.18), fill_color=color, border_color=None, radius=5000)
    txt(s, label, lx + Inches(0.25), ry2, Inches(3.5), Inches(0.26), size=Pt(8.5), color=TEXT)

txt(s, "4 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 5 — API Connections
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "API Connections", "Three external services · sequential call order per NPC turn")

# Call order strip
strip_y = Inches(0.75)
for i, (label, color) in enumerate([("1. Whisper STT", BLUE), ("→", MUTED), ("2. Claude LLM", PURPLE), ("→", MUTED), ("3. ElevenLabs TTS", GREEN)]):
    if label in ("→",):
        txt(s, label, Inches(0.45) + i * Inches(2.1), strip_y, Inches(0.4), Inches(0.3), size=Pt(14), color=MUTED, align=PP_ALIGN.CENTER)
    else:
        rect(s, Inches(0.45) + i * Inches(2.1), strip_y, Inches(1.9), Inches(0.32),
             fill_color=SURFACE, border_color=color, radius=15000)
        txt(s, label, Inches(0.45) + i * Inches(2.1), strip_y, Inches(1.9), Inches(0.32),
            size=Pt(9), bold=True, color=color, align=PP_ALIGN.CENTER)

# Table
headers = ["API", "Endpoint", "Auth Header", "Input", "Output", "Notes"]
col_widths = [Inches(1.3), Inches(2.9), Inches(1.55), Inches(1.9), Inches(2.2), Inches(2.75)]
rows = [
    [("Whisper STT", BLUE),
     "POST /v1/audio/transcriptions",
     "Authorization: Bearer",
     "WAV 16kHz mono\n(Windows waveIn)",
     "Plain text transcript",
     "4× double buffers 0.5s each"],
    [("Claude LLM", PURPLE),
     "POST /v1/messages",
     "x-api-key",
     "System prompt +\nhistory + user emotion",
     'JSON: dialogue,\nemotion_update[8],\nitem_give',
     "claude-sonnet-4-6 · 512 tok max\n0.5s rate limit · 3× retry backoff"],
    [("ElevenLabs TTS", GREEN),
     "POST /v1/text-to-speech\n/{voice_id}/with-timestamps",
     "xi-api-key",
     "Dialogue text +\nvoice config",
     "Base64 PCM 24kHz +\nchar-level alignment",
     "eleven_flash_v2_5\nUSoundWaveProcedural playback"],
]
table_y = Inches(1.22)
make_table(s, headers, rows, Inches(0.45), table_y, W - Inches(0.9), col_widths, row_height=Inches(0.58))

# Bottom cards
card_y2 = Inches(4.6)
card_h2 = Inches(0.95)
card_w2 = (W - Inches(0.9) - Inches(0.2)) / 3
for i, (title, color, lines) in enumerate([
    ("🔑  Key Storage", BLUE, ["Keys from environment variables:", "OPENAI_API_KEY", "ANTHROPIC_API_KEY", "ELEVENLABS_API_KEY"]),
    ("⚡  Rate Limiting", AMBER, ["Claude: 0.5s min interval", "429 / 5xx → exponential backoff", "1s → 2s → 4s ± 25% jitter", "Max 3 retries per request"]),
    ("🔄  Async Pattern", GREEN, ["All HTTP callbacks dispatch via:", "AsyncTask(GameThread, ...)", "Ensures UObject/delegate safety", "No frame dependency"]),
]):
    cx3 = Inches(0.45) + i * (card_w2 + Inches(0.1))
    rect(s, cx3, card_y2, card_w2, card_h2, fill_color=SURFACE, border_color=BORDER, radius=15000)
    txt(s, title, cx3+Inches(0.1), card_y2+Inches(0.08), card_w2-Inches(0.2), Inches(0.24), size=Pt(9.5), bold=True, color=color)
    for j, line in enumerate(lines):
        txt(s, line, cx3+Inches(0.1), card_y2+Inches(0.33)+j*Inches(0.155), card_w2-Inches(0.2), Inches(0.18),
            size=Pt(8), color=MUTED if j > 0 else TEXT)

txt(s, "5 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 6 — Claude Prompt & Response Contract
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "Claude Prompt & Response Contract", "Structured JSON in / structured JSON out — zero freeform text")

panel_y = Inches(0.72)
panel_h = H - Inches(1.05)
panel_w = (W - Inches(1.05)) / 2

# Left: system prompt
rect(s, Inches(0.45), panel_y, panel_w, panel_h, fill_color=SURFACE, border_color=BORDER, radius=15000)
txt(s, "System Prompt Structure", Inches(0.6), panel_y + Inches(0.1), panel_w - Inches(0.3), Inches(0.24),
    size=Pt(10), bold=True, color=TEXT)

prompt_lines = [
    ("[NPC Persona]",                 BLUE),
    ("  Name, backstory, speaking style,", MUTED),
    ("  personality traits",            MUTED),
    ("[Emotion Vocabulary]",            BLUE),
    ("  Plutchik 8 emotions defined",   MUTED),
    ("[Inventory Catalogue]",           BLUE),
    ("  Items + unlock conditions",     MUTED),
    ("[Response Format Schema]",        BLUE),
    ("  Strict JSON — no freeform",     MUTED),
    ("[Current PAD State]  ← per-turn", AMBER),
    ("  Pleasure: 0.4  Arousal: 0.2",  MUTED),
    ("[Player Emotion]  ← ONNX vision", AMBER),
    ('  Detected: neutral (0.82)',      MUTED),
    ("[Conversation History]  ← 20-turn buffer", AMBER),
    ('  [user] "…"  [assistant] "…"',  MUTED),
]
for j, (line, color) in enumerate(prompt_lines):
    ty = panel_y + Inches(0.42) + j * Inches(0.38)
    txt(s, line, Inches(0.6), ty, panel_w - Inches(0.3), Inches(0.36),
        size=Pt(8.5), color=color, wrap=False)

# Right: JSON response
rx = Inches(0.45) + panel_w + Inches(0.15)
rect(s, rx, panel_y, panel_w, panel_h, fill_color=SURFACE, border_color=BORDER, radius=15000)
txt(s, "Required JSON Response Schema", rx + Inches(0.15), panel_y + Inches(0.1), panel_w - Inches(0.3), Inches(0.24),
    size=Pt(10), bold=True, color=TEXT)

json_lines = [
    ("{",                                                   TEXT),
    ('  "dialogue":  "The spoken response text",',          BLUE),
    ("  // → routed directly to ElevenLabs TTS",            MUTED),
    ("",                                                    TEXT),
    ('  "emotion_update": {',                               RED),
    ('    "joy": 0.2,  "trust": 0.5,  "fear": -0.1,',     AMBER),
    ('    "surprise": 0.0,  "sadness": 0.0,',              AMBER),
    ('    "disgust": 0.0,  "anger": 0.0,',                 AMBER),
    ('    "anticipation": 0.3',                             AMBER),
    ("  },  // → PAD state machine → FACS curves",         MUTED),
    ("",                                                    TEXT),
    ('  "item_give": "key_of_the_old_tower"',               PURPLE),
    ("  // → InventoryComponent (null if none)",            MUTED),
    ("}",                                                   TEXT),
]
for j, (line, color) in enumerate(json_lines):
    ty = panel_y + Inches(0.42) + j * Inches(0.38)
    txt(s, line, rx + Inches(0.15), ty, panel_w - Inches(0.3), Inches(0.36),
        size=Pt(8.5), color=color, wrap=False)

# Chips at bottom
ccy = H - Inches(0.5)
cx4 = rx + Inches(0.15)
for text, color in [("🔵 → TTS Audio", BLUE), ("🔴 → Emotion Engine", RED), ("🟣 → Inventory", PURPLE)]:
    w4 = chip(s, text, cx4, ccy, color)
    cx4 += w4 + Inches(0.15)

txt(s, "6 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 7 — ML / AI Systems
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "ML / AI Systems", "Six AI components — three deployment tiers")

headers = ["System", "Type", "Input", "Output", "Role", "Deploy"]
col_widths = [Inches(1.7), Inches(1.8), Inches(1.9), Inches(2.0), Inches(3.0), Inches(1.5)]

rows = [
    [("Claude (Anthropic)", BLUE), "LLM — transformer", "Text prompt + history",
     "Structured JSON", "Dialogue + emotional intent generation", ("☁ External API", BLUE)],
    [("ElevenLabs TTS", GREEN), "Neural voice synthesis", "Text + voice config",
     "PCM audio + phoneme timestamps", "Realistic voice output + lip sync data source", ("☁ External API", BLUE)],
    [("OpenAI Whisper", AMBER), "ASR — encoder-decoder", "WAV audio (16kHz)",
     "Text transcript", "Player voice → text for Claude prompt", ("☁ External API", BLUE)],
    [("PAD Emotion Engine", RED), "Graph state machine", "Emotion delta (Plutchik 8)",
     "3D PAD vector + named state", "Continuous emotional state tracking and decay", ("⚙ Runtime C++", GREEN)],
    [("Facial Classifier", PURPLE), "CNN — ONNX (8-class)", "Camera frame (OpenCV DNN)",
     "Emotion label + confidence", "Player emotional state → injected into Claude context", ("▣ On-device ONNX", PURPLE)],
    [("Hand Landmark Detector", TEAL), "Regression — ONNX", "Camera frame",
     "21-point hand skeleton", "Pinch/Spread/Rotate → inventory / NPC reaction", ("▣ On-device ONNX", PURPLE)],
]

make_table(s, headers, rows, Inches(0.45), Inches(0.78), W - Inches(0.9), col_widths, row_height=Inches(0.72))

# Bottom tier cards
cy5 = Inches(5.5)
ch5 = Inches(1.15)
cw5 = (W - Inches(0.9) - Inches(0.2)) / 3
for i, (icon, title, color, desc) in enumerate([
    ("☁", "External APIs (3)", BLUE,   "Claude · Whisper · ElevenLabs. Highest latency 100ms–2s. Require internet + API keys. Async with retry."),
    ("▣", "On-device ONNX (2)", PURPLE, "Facial expression + hand landmark models. Run locally via OpenCV DNN. 10 FPS (face) / 15 FPS (hand). No API call needed."),
    ("⚙", "Runtime Engine (1)", GREEN,  "PAD emotion state machine — pure C++ per-frame tick. Integrates Claude emotion deltas with 0.05/s decay rate."),
]):
    cx5 = Inches(0.45) + i * (cw5 + Inches(0.1))
    rect(s, cx5, cy5, cw5, ch5, fill_color=SURFACE, border_color=color, radius=15000)
    txt(s, f"{icon}  {title}", cx5+Inches(0.12), cy5+Inches(0.1), cw5-Inches(0.24), Inches(0.26), size=Pt(10), bold=True, color=color)
    txt(s, desc, cx5+Inches(0.12), cy5+Inches(0.38), cw5-Inches(0.24), ch5-Inches(0.45), size=Pt(8.5), color=MUTED, wrap=True)

txt(s, "7 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 8 — PAD Emotion State Machine
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "PAD Emotion State Machine", "Pleasure · Arousal · Dominance — continuous 3D emotion space")

# Emotion grid
emotions = [
    ("Joy",         AMBER,  "P:+0.8  A:+0.5  D:+0.6", 80),
    ("Sadness",     BLUE,   "P:-0.7  A:-0.3  D:-0.5", 20),
    ("Anger",       RED,    "P:-0.5  A:+0.7  D:+0.8", 70),
    ("Fear",        PURPLE, "P:-0.6  A:+0.6  D:-0.7", 30),
    ("Trust",       GREEN,  "P:+0.6  A:+0.1  D:+0.3", 60),
    ("Surprise",    TEAL,   "P:+0.2  A:+0.8  D:-0.2", 50),
    ("Anticipation",AMBER,  "P:+0.3  A:+0.4  D:+0.5", 55),
    ("Neutral",     MUTED,  "P: 0.0  A: 0.0  D: 0.0", 50),
]
ew = Inches(1.5)
eh = Inches(0.75)
ex0 = Inches(0.45)
ey0 = Inches(0.82)
for i, (name, color, vec, pct) in enumerate(emotions):
    col = i % 4
    row = i // 4
    ex = ex0 + col * (ew + Inches(0.08))
    ey = ey0 + row * (eh + Inches(0.08))
    fills2 = {AMBER: RGBColor(0x1f,0x18,0x08), BLUE: RGBColor(0x0d,0x1d,0x2e), RED: RGBColor(0x1f,0x0d,0x0d),
              PURPLE: RGBColor(0x1a,0x14,0x28), GREEN: RGBColor(0x0d,0x1e,0x12), TEAL: RGBColor(0x0c,0x1e,0x18), MUTED: SURFACE}
    rect(s, ex, ey, ew, eh, fill_color=fills2.get(color, SURFACE), border_color=color, radius=15000)
    txt(s, name, ex+Inches(0.08), ey+Inches(0.06), ew-Inches(0.16), Inches(0.22), size=Pt(9.5), bold=True, color=color)
    txt(s, vec,  ex+Inches(0.08), ey+Inches(0.28), ew-Inches(0.16), Inches(0.2),  size=Pt(7.5), color=MUTED)
    # bar
    rect(s, ex+Inches(0.08), ey+Inches(0.52), ew-Inches(0.16), Inches(0.07), fill_color=SURF2, border_color=None, radius=5000)
    bar_w = max((ew-Inches(0.16)) * pct / 100, Inches(0.05))
    rect(s, ex+Inches(0.08), ey+Inches(0.52), bar_w, Inches(0.07), fill_color=color, border_color=None, radius=5000)

# Right panel — how it works
rx2 = Inches(6.9)
rw2 = Inches(6.0)
py = Inches(0.82)
ph = Inches(0.85)
for title, color2, body in [
    ("Signal Processing", TEXT,
     "Claude response → emotion_update[8] → highest-strength signal drives PAD delta. Multiple signals blend. Intensity decays 0.05/s toward neutral when idle."),
    ("Graph Transitions", TEXT,
     "EmotionGraphDataAsset: nodes = emotions, edges = rules. Each edge has conditions (PAD distance, time-in-state, signal strength). Lowest-cost valid path wins."),
    ("Per-NPC Cost Map", TEXT,
     "Stoic NPC: high cost for Sadness, low for Neutral. Volatile NPC: low cost for Anger. Personality encoded without changing the algorithm."),
    ("Downstream Output", TEXT,
     "PAD state → FACS blend shape weights (face) · Body animation state (Idle/Thinking/Speaking) · Inventory unlock threshold check."),
]:
    rect(s, rx2, py, rw2, ph, fill_color=SURFACE, border_color=BORDER, radius=15000)
    txt(s, title, rx2+Inches(0.12), py+Inches(0.08), rw2-Inches(0.24), Inches(0.22), size=Pt(9.5), bold=True, color=BLUE)
    txt(s, body,  rx2+Inches(0.12), py+Inches(0.3),  rw2-Inches(0.24), ph-Inches(0.35), size=Pt(8.5), color=MUTED, wrap=True)
    py += ph + Inches(0.1)

txt(s, "8 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 9 — Animation Synthesis Pipeline
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "Animation Synthesis Pipeline", "Three parallel tracks driven from one shared source")

# Source bar
src_y = Inches(0.78)
rect(s, Inches(0.45), src_y, W - Inches(0.9), Inches(0.38), fill_color=SURFACE, border_color=BORDER, radius=15000)
txt(s, "Source:  PAD emotional state  +  ElevenLabs character-level alignment  →  three parallel animation tracks",
    Inches(0.6), src_y + Inches(0.07), W - Inches(1.2), Inches(0.26), size=Pt(9.5), color=MUTED)

tracks = [
    ("A — Lip Sync", BLUE, RGBColor(0x0d,0x1d,0x2e), [
        "Character timestamps → viseme schedule (FPhonemeVisemeMapper)",
        "Digraph handling (th, sh, ch, ph, ng) + silence gap insertion >80ms",
        "Per-frame: sample schedule at playbackElapsed seconds",
        "Smoothstep interpolation between bracketing viseme keys",
        "Asymmetric smoothing: closure fast-close 50/s · slow-open 7/s",
        "→ ARKit FACS morph targets via Metahuman RigLogic",
    ]),
    ("B — Facial Expression", AMBER, RGBColor(0x1f,0x18,0x08), [
        "PAD state → EEmotionType → BlendShapeMappingDataAsset lookup",
        "Maps emotion → FACS AU curve names + weights",
        "e.g. Joy → cheekRaiser 0.7, mouthCornerPull 0.6",
        "Thinking pose: brow-only curves, auto-clears on TTS start or 15s timeout",
        "FInterpTo smoothing at speed 4.0 per frame",
        "→ SetFaceControl via reflection on Face AnimBP",
    ]),
    ("C — Body Language (FK)", GREEN, RGBColor(0x0d,0x1e,0x12), [
        "3-state machine: Idle / Thinking / Speaking — blended by alphas",
        "OnTranscriptReady → Thinking · OnSpeechStarted → Speaking",
        "Gesture cycle: cosine blend Speaking ↔ SpeakingGesture (8s period)",
        "Sine overlays: breathing 0.25Hz · head drift 0.05Hz · nods 0.5Hz",
        "Shoulder sway micro-motion during speech",
        "→ 15 bones via OnBoneTransformsFinalizedMC delegate",
    ]),
]

col_w = (W - Inches(0.9) - Inches(0.2)) / 3
track_y = Inches(1.3)
track_h = H - Inches(1.65)

for i, (title, color, fill, steps) in enumerate(tracks):
    cx = Inches(0.45) + i * (col_w + Inches(0.1))
    # Header
    rect(s, cx, track_y, col_w, Inches(0.36), fill_color=fill, border_color=color, radius=15000)
    txt(s, title, cx, track_y, col_w, Inches(0.36), size=Pt(10), bold=True, color=color, align=PP_ALIGN.CENTER)
    # Body
    rect(s, cx, track_y + Inches(0.36), col_w, track_h - Inches(0.36), fill_color=SURFACE, border_color=color, radius=15000)
    for j, step in enumerate(steps):
        sy = track_y + Inches(0.5) + j * Inches(0.52)
        rect(s, cx + Inches(0.1), sy + Inches(0.05), Inches(0.08), Inches(0.08),
             fill_color=color, border_color=None, radius=5000)
        txt(s, step, cx + Inches(0.25), sy, col_w - Inches(0.35), Inches(0.5),
            size=Pt(8.5), color=TEXT, wrap=True)

txt(s, "9 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 10 — Vision Input
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "Vision Input: Facial & Gesture Recognition", "On-device ONNX — no extra API cost · private · zero latency vs cloud")

# Pipeline diagram
px = Inches(0.45)
py = Inches(0.85)
bh2 = Inches(0.4)
bw2 = Inches(2.5)

# Camera → splits to face + hand
rect(s, px, py + Inches(0.7), bw2, bh2, fill_color=RGBColor(0x0d,0x1d,0x2e), border_color=BLUE, radius=15000)
txt(s, "📷  Webcam Frame\n(UCameraManagerSubsystem)", px, py + Inches(0.7), bw2, bh2,
    size=Pt(8.5), color=BLUE, align=PP_ALIGN.CENTER)

# Face branch
fx = px + bw2 + Inches(0.5)
fy_face = py
fy_hand = py + Inches(1.5)

for fy, label, color, fill, notes in [
    (fy_face, "OpenCV DNN  →  ONNX\nFacial Classifier (8-class CNN)", AMBER, RGBColor(0x1f,0x18,0x08),
     ["~10 FPS timer (not tick)", "Output: emotion + confidence", "Threshold: 0.5 confidence", "→ Injected into Claude prompt"]),
    (fy_hand, "ONNX Hand Landmark\nDetector (21-point regression)", PURPLE, RGBColor(0x1a,0x14,0x28),
     ["~15 FPS timer", "Classifies: Pinch / Spread / Rotate", "Spindle (two-hand distance)", "→ Inventory + NPC reactions"]),
]:
    rect(s, fx, fy, bw2, bh2, fill_color=fill, border_color=color, radius=15000)
    txt(s, label, fx, fy, bw2, bh2, size=Pt(8.5), color=color, align=PP_ALIGN.CENTER)
    # Notes card
    rect(s, fx + bw2 + Inches(0.4), fy, Inches(2.4), bh2 * 1.6, fill_color=SURFACE, border_color=BORDER, radius=15000)
    for k, note in enumerate(notes):
        txt(s, f"• {note}", fx + bw2 + Inches(0.5), fy + Inches(0.04) + k * Inches(0.16), Inches(2.2), Inches(0.18),
            size=Pt(8), color=MUTED)

# Data flow cards (right side)
rx3 = Inches(8.5)
ry3 = Inches(0.82)
rw3 = Inches(4.6)

for title, color3, body3 in [
    ("Face → Claude Context", AMBER,
     'FDetectedUserEmotion { type, confidence, probs[8] }\n→ DialogueComponent annotates next user message\n→ Claude sees player emotion and adjusts NPC response'),
    ("Gesture → Inventory Bridge", PURPLE,
     'Pinch on InspectableItem → ObjectInspectWidget opens\nNPC reacts to item inspection\nInventory unlock conditions may trigger'),
    ("Fallback Handling", GREEN,
     'No face detected → keep last emotion or default Neutral\nHand not visible → timeout, reset gesture state\nFails gracefully without breaking dialogue pipeline'),
]:
    rect(s, rx3, ry3, rw3, Inches(1.5), fill_color=SURFACE, border_color=BORDER, radius=15000)
    txt(s, title, rx3+Inches(0.12), ry3+Inches(0.1), rw3-Inches(0.24), Inches(0.24), size=Pt(9.5), bold=True, color=color3)
    txt(s, body3, rx3+Inches(0.12), ry3+Inches(0.35), rw3-Inches(0.24), Inches(1.05), size=Pt(8.5), color=MUTED, wrap=True)
    ry3 += Inches(1.6)

txt(s, "10 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 11 — Inventory & Emotion-Gated Mechanics
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "Inventory & Emotion-Gated Mechanics", "LLM reasoning gates gameplay progression — zero scripted branches")

left_w = Inches(6.2)
right_x = Inches(6.85)
right_w = Inches(6.1)
top11 = Inches(0.78)

# Unlock condition struct
rect(s, Inches(0.45), top11, left_w, Inches(1.5), fill_color=SURFACE, border_color=BORDER, radius=15000)
txt(s, "FEmotionUnlockCondition  (per item)", Inches(0.6), top11 + Inches(0.1), left_w - Inches(0.3), Inches(0.24),
    size=Pt(9.5), bold=True, color=TEXT)
code_lines = [
    ("EmotionType:  ETrust,",               AMBER),
    ("MinIntensity: 0.7,    // PAD threshold",    MUTED),
    ("MinDuration:  10.0s,  // must be sustained", MUTED),
    ('Keywords:     ["key", "tower", "secret"]',  GREEN),
]
for j, (line, color) in enumerate(code_lines):
    txt(s, line, Inches(0.7), top11 + Inches(0.42) + j * Inches(0.24), left_w - Inches(0.4), Inches(0.22),
        size=Pt(8.5), color=color)

# Unlock chain flow
flow_y = Inches(2.42)
chain = [
    ("Claude emotion_update raises Trust", RED, RGBColor(0x1f,0x0d,0x0d)),
    ("PAD state: Trust > 0.7  sustained > 10s", PURPLE, RGBColor(0x1a,0x14,0x28)),
    ('Keyword "key" appears in dialogue',   AMBER, RGBColor(0x1f,0x18,0x08)),
    ('Claude returns  item_give: "key_of_the_old_tower"', GREEN, RGBColor(0x0d,0x1e,0x12)),
    ("InventoryComponent::TryGiveItem() → OnItemGiven", GREEN, RGBColor(0x0d,0x1e,0x12)),
]
fw = left_w - Inches(0.1)
for j, (label, color, fill) in enumerate(chain):
    fy2 = flow_y + j * Inches(0.58)
    flow_box(s, label, Inches(0.45), fy2, fw, Inches(0.42), fill, color)
    if j < len(chain) - 1:
        arrow_down(s, Inches(0.45) + fw/2, fy2 + Inches(0.42))

# Right panel
for title, color4, body4, y4 in [
    ("Why It Matters", PURPLE,
     "LLM reasoning directly gates gameplay. No scripted branches. No dialogue trees. The NPC decides when to give the item based on its emotional read of the conversation.",
     top11),
    ("Conversation Arc", BLUE,
     "Trust accumulates across turns. Emotional state persists for the full session. Player must build genuine rapport — mechanical exploitation is bounded by PAD decay.",
     top11 + Inches(1.65)),
    ("Fallback Inputs", GREEN,
     "Whisper STT fails 30s → FallbackManagerComponent switches to text widget. TTS fails → DialogueFallbackWidget shows text-only response. Zero-downtime degradation.",
     top11 + Inches(3.3)),
]:
    rect(s, right_x, y4, right_w, Inches(1.5), fill_color=SURFACE, border_color=BORDER, radius=15000)
    txt(s, title, right_x + Inches(0.12), y4 + Inches(0.1), right_w - Inches(0.24), Inches(0.24), size=Pt(9.5), bold=True, color=color4)
    txt(s, body4, right_x + Inches(0.12), y4 + Inches(0.36), right_w - Inches(0.24), Inches(1.0), size=Pt(8.5), color=MUTED, wrap=True)

txt(s, "11 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ══════════════════════════════════════════════════════════════════════════════
# SLIDE 12 — Summary & Open Challenges
# ══════════════════════════════════════════════════════════════════════════════
s = add_slide()
section_header(s, "Summary & Open Challenges", "What's been built · what's still open")

col_w12 = (W - Inches(0.9) - Inches(0.15)) / 2
top12 = Inches(0.78)
h12 = Inches(5.8)

# Achievements (left)
rect(s, Inches(0.45), top12, col_w12, h12, fill_color=SURFACE, border_color=GREEN, radius=15000)
txt(s, "✓  Achievements", Inches(0.6), top12 + Inches(0.12), col_w12 - Inches(0.3), Inches(0.28), size=Pt(11), bold=True, color=GREEN)
achievements = [
    "End-to-end real-time conversational NPC — zero scripted dialogue lines",
    "Unified PAD emotional state drives voice, face, and body simultaneously",
    "Character-level lip sync from ElevenLabs alignment with asymmetric smoothing",
    "Procedural full-body FK animation — no AnimBP assets required",
    "On-device ONNX vision keeps player sensing local and private",
    "Emotion-gated item unlock — LLM reasoning gates gameplay progression",
    "Modular subsystem architecture — new NPC via data asset, no C++ recompile",
]
for j, a in enumerate(achievements):
    ay = top12 + Inches(0.5) + j * Inches(0.72)
    rect(s, Inches(0.6), ay, Inches(0.22), Inches(0.22), fill_color=GREEN, border_color=None, radius=5000)
    txt(s, a, Inches(0.9), ay - Inches(0.02), col_w12 - Inches(0.6), Inches(0.65), size=Pt(9), color=TEXT, wrap=True)

# Open Challenges (right)
rx12 = Inches(0.45) + col_w12 + Inches(0.15)
rect(s, rx12, top12, col_w12, h12, fill_color=SURFACE, border_color=AMBER, radius=15000)
txt(s, "△  Open Challenges", rx12 + Inches(0.15), top12 + Inches(0.12), col_w12 - Inches(0.3), Inches(0.28), size=Pt(11), bold=True, color=AMBER)
challenges = [
    "LLM API latency (~1–2s per turn) breaks real-time immersion at scale",
    "ONNX model accuracy degrades under variable lighting or partial occlusion",
    "PAD emotional state resets between sessions — no persistence layer yet",
    "Voice cloning ethics + ElevenLabs licensing boundaries for shipped games",
    "Single NPC only — multi-NPC coordination and shared emotional memory TBD",
]
for j, c in enumerate(challenges):
    cy6 = top12 + Inches(0.5) + j * Inches(0.72)
    rect(s, rx12 + Inches(0.15), cy6, Inches(0.22), Inches(0.22), fill_color=AMBER, border_color=None, radius=5000)
    txt(s, c, rx12 + Inches(0.45), cy6 - Inches(0.02), col_w12 - Inches(0.6), Inches(0.65), size=Pt(9), color=TEXT, wrap=True)

# Stack chips
ccy12 = H - Inches(0.5)
cx12 = Inches(0.45)
for text, color in [("UE 5.7", BLUE), ("Claude API", PURPLE), ("ElevenLabs", GREEN), ("Whisper", AMBER), ("ONNX Runtime", TEAL), ("Metahuman RigLogic", BLUE)]:
    w12c = chip(s, text, cx12, ccy12, color)
    cx12 += w12c + Inches(0.12)

# Footer quote
txt(s, '"All dialogue emerges from model inference. Zero hand-authored lines."',
    Inches(0.45), H - Inches(0.88), W - Inches(0.9), Inches(0.28),
    size=Pt(9.5), italic=True, color=MUTED, align=PP_ALIGN.CENTER)

txt(s, "12 / 12", W - Inches(0.9), H - Inches(0.3), Inches(0.8), Inches(0.25), size=Pt(8), color=MUTED, align=PP_ALIGN.RIGHT)


# ── Save ───────────────────────────────────────────────────────────────────
output = "c:/Users/alexx/OneDrive/Documents/GitHub/LLM-NPC/slide-deck.pptx"
prs.save(output)
print(f"Saved: {output}")
print(f"Slides: {len(prs.slides)}")
