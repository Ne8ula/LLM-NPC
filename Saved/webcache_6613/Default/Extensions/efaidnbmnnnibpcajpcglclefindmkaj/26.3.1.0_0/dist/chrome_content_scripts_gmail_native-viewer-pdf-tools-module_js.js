export const __webpack_esm_id__ = "chrome_content_scripts_gmail_native-viewer-pdf-tools-module_js";
export const __webpack_esm_ids__ = ["chrome_content_scripts_gmail_native-viewer-pdf-tools-module_js"];
export const __webpack_esm_modules__ = {

/***/ "./chrome/content_scripts/gmail lazy recursive referencedExports: default":
/*!****************************************************************************************!*\
  !*** ./chrome/content_scripts/gmail/ lazy referencedExports: default namespace object ***!
  \****************************************************************************************/
/***/ ((module) => {

function webpackEmptyAsyncContext(req) {
	// Here Promise.resolve().then() is used instead of new Promise() to prevent
	// uncaught exception popping up in devtools
	return Promise.resolve().then(() => {
		var e = new Error("Cannot find module '" + req + "'");
		e.code = 'MODULE_NOT_FOUND';
		throw e;
	});
}
webpackEmptyAsyncContext.keys = () => ([]);
webpackEmptyAsyncContext.resolve = webpackEmptyAsyncContext;
webpackEmptyAsyncContext.id = "./chrome/content_scripts/gmail lazy recursive referencedExports: default";
module.exports = webpackEmptyAsyncContext;

/***/ }),

/***/ "./chrome/content_scripts/gmail/native-viewer-pdf-tools-module.js":
/*!************************************************************************!*\
  !*** ./chrome/content_scripts/gmail/native-viewer-pdf-tools-module.js ***!
  \************************************************************************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

__webpack_require__.r(__webpack_exports__);
/* harmony export */ __webpack_require__.d(__webpack_exports__, {
/* harmony export */   removePdfToolsDropdown: () => (/* binding */ removePdfToolsDropdown),
/* harmony export */   renderPdfToolsDropdown: () => (/* binding */ renderPdfToolsDropdown)
/* harmony export */ });
/* harmony import */ var _state_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./state.js */ "./chrome/content_scripts/gmail/state.js");
/* harmony import */ var _utils_util_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ../utils/util.js */ "./chrome/content_scripts/utils/util.js");
/* harmony import */ var _util_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./util.js */ "./chrome/content_scripts/gmail/util.js");
/* harmony import */ var _utils_fte_utils_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ../utils/fte-utils.js */ "./chrome/content_scripts/utils/fte-utils.js");
function _typeof(o) { "@babel/helpers - typeof"; return _typeof = "function" == typeof Symbol && "symbol" == typeof Symbol.iterator ? function (o) { return typeof o; } : function (o) { return o && "function" == typeof Symbol && o.constructor === Symbol && o !== Symbol.prototype ? "symbol" : typeof o; }, _typeof(o); }
function _regenerator() { /*! regenerator-runtime -- Copyright (c) 2014-present, Facebook, Inc. -- license (MIT): https://github.com/babel/babel/blob/main/packages/babel-helpers/LICENSE */ var e, t, r = "function" == typeof Symbol ? Symbol : {}, n = r.iterator || "@@iterator", o = r.toStringTag || "@@toStringTag"; function i(r, n, o, i) { var c = n && n.prototype instanceof Generator ? n : Generator, u = Object.create(c.prototype); return _regeneratorDefine2(u, "_invoke", function (r, n, o) { var i, c, u, f = 0, p = o || [], y = !1, G = { p: 0, n: 0, v: e, a: d, f: d.bind(e, 4), d: function d(t, r) { return i = t, c = 0, u = e, G.n = r, a; } }; function d(r, n) { for (c = r, u = n, t = 0; !y && f && !o && t < p.length; t++) { var o, i = p[t], d = G.p, l = i[2]; r > 3 ? (o = l === n) && (u = i[(c = i[4]) ? 5 : (c = 3, 3)], i[4] = i[5] = e) : i[0] <= d && ((o = r < 2 && d < i[1]) ? (c = 0, G.v = n, G.n = i[1]) : d < l && (o = r < 3 || i[0] > n || n > l) && (i[4] = r, i[5] = n, G.n = l, c = 0)); } if (o || r > 1) return a; throw y = !0, n; } return function (o, p, l) { if (f > 1) throw TypeError("Generator is already running"); for (y && 1 === p && d(p, l), c = p, u = l; (t = c < 2 ? e : u) || !y;) { i || (c ? c < 3 ? (c > 1 && (G.n = -1), d(c, u)) : G.n = u : G.v = u); try { if (f = 2, i) { if (c || (o = "next"), t = i[o]) { if (!(t = t.call(i, u))) throw TypeError("iterator result is not an object"); if (!t.done) return t; u = t.value, c < 2 && (c = 0); } else 1 === c && (t = i["return"]) && t.call(i), c < 2 && (u = TypeError("The iterator does not provide a '" + o + "' method"), c = 1); i = e; } else if ((t = (y = G.n < 0) ? u : r.call(n, G)) !== a) break; } catch (t) { i = e, c = 1, u = t; } finally { f = 1; } } return { value: t, done: y }; }; }(r, o, i), !0), u; } var a = {}; function Generator() {} function GeneratorFunction() {} function GeneratorFunctionPrototype() {} t = Object.getPrototypeOf; var c = [][n] ? t(t([][n]())) : (_regeneratorDefine2(t = {}, n, function () { return this; }), t), u = GeneratorFunctionPrototype.prototype = Generator.prototype = Object.create(c); function f(e) { return Object.setPrototypeOf ? Object.setPrototypeOf(e, GeneratorFunctionPrototype) : (e.__proto__ = GeneratorFunctionPrototype, _regeneratorDefine2(e, o, "GeneratorFunction")), e.prototype = Object.create(u), e; } return GeneratorFunction.prototype = GeneratorFunctionPrototype, _regeneratorDefine2(u, "constructor", GeneratorFunctionPrototype), _regeneratorDefine2(GeneratorFunctionPrototype, "constructor", GeneratorFunction), GeneratorFunction.displayName = "GeneratorFunction", _regeneratorDefine2(GeneratorFunctionPrototype, o, "GeneratorFunction"), _regeneratorDefine2(u), _regeneratorDefine2(u, o, "Generator"), _regeneratorDefine2(u, n, function () { return this; }), _regeneratorDefine2(u, "toString", function () { return "[object Generator]"; }), (_regenerator = function _regenerator() { return { w: i, m: f }; })(); }
function _regeneratorDefine2(e, r, n, t) { var i = Object.defineProperty; try { i({}, "", {}); } catch (e) { i = 0; } _regeneratorDefine2 = function _regeneratorDefine(e, r, n, t) { function o(r, n) { _regeneratorDefine2(e, r, function (e) { return this._invoke(r, n, e); }); } r ? i ? i(e, r, { value: n, enumerable: !t, configurable: !t, writable: !t }) : e[r] = n : (o("next", 0), o("throw", 1), o("return", 2)); }, _regeneratorDefine2(e, r, n, t); }
function asyncGeneratorStep(n, t, e, r, o, a, c) { try { var i = n[a](c), u = i.value; } catch (n) { return void e(n); } i.done ? t(u) : Promise.resolve(u).then(r, o); }
function _asyncToGenerator(n) { return function () { var t = this, e = arguments; return new Promise(function (r, o) { var a = n.apply(t, e); function _next(n) { asyncGeneratorStep(a, r, o, _next, _throw, "next", n); } function _throw(n) { asyncGeneratorStep(a, r, o, _next, _throw, "throw", n); } _next(void 0); }); }; }
function ownKeys(e, r) { var t = Object.keys(e); if (Object.getOwnPropertySymbols) { var o = Object.getOwnPropertySymbols(e); r && (o = o.filter(function (r) { return Object.getOwnPropertyDescriptor(e, r).enumerable; })), t.push.apply(t, o); } return t; }
function _objectSpread(e) { for (var r = 1; r < arguments.length; r++) { var t = null != arguments[r] ? arguments[r] : {}; r % 2 ? ownKeys(Object(t), !0).forEach(function (r) { _defineProperty(e, r, t[r]); }) : Object.getOwnPropertyDescriptors ? Object.defineProperties(e, Object.getOwnPropertyDescriptors(t)) : ownKeys(Object(t)).forEach(function (r) { Object.defineProperty(e, r, Object.getOwnPropertyDescriptor(t, r)); }); } return e; }
function _defineProperty(e, r, t) { return (r = _toPropertyKey(r)) in e ? Object.defineProperty(e, r, { value: t, enumerable: !0, configurable: !0, writable: !0 }) : e[r] = t, e; }
function _toPropertyKey(t) { var i = _toPrimitive(t, "string"); return "symbol" == _typeof(i) ? i : i + ""; }
function _toPrimitive(t, r) { if ("object" != _typeof(t) || !t) return t; var e = t[Symbol.toPrimitive]; if (void 0 !== e) { var i = e.call(t, r || "default"); if ("object" != _typeof(i)) return i; throw new TypeError("@@toPrimitive must return a primitive value."); } return ("string" === r ? String : Number)(t); }
/*************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 *  Copyright 2026 Adobe Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/

/**
 * PDF Tools Native Viewer Touch Point Module
 *
 * This module contains all PDF Tools dropdown specific logic for Gmail native viewer.
 * It is dynamically imported when the PDF Tools feature flag is enabled.
 */

/* global initDcLocalStorage, gmailPdfToolsFteCoachmark */






// PDF Tools specific constants
var PDF_TOOLS_FTE_TOOLTIP_STORAGE_KEY = "acrobat-gmail-pdf-tools-fte-config";
var DIRECT_VERB_FTE_DISMISSED_ANALYTICS_EVENT = "DCBrowserExt:DirectVerb:Fte:Dismissed";
var PDF_TOOLS_TOUCHPOINT_CLASS = "acrobat-native-viewer-pdf-tools-touchpoint";

/**
 * Handle click outside FTE tooltip for PDF Tools (Shadow DOM aware)
 */
var handleFteClickOutside = function handleFteClickOutside(event, tooltip) {
  var isInShadowDOM = tooltip.getRootNode() instanceof ShadowRoot;
  if (isInShadowDOM) {
    var composedPath = event.composedPath();
    var isInsideTooltip = composedPath.includes(tooltip);
    if (!isInsideTooltip) {
      tooltip.remove();
      _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].fteToolTip.eligibleFte.type = "";
      (0,_utils_util_js__WEBPACK_IMPORTED_MODULE_1__.sendAnalytics)([[DIRECT_VERB_FTE_DISMISSED_ANALYTICS_EVENT, {
        source: "gmail_chrome",
        workflow: "pdf_tools"
      }]]);
      if (tooltip.clickOutsideHandler) {
        document.removeEventListener("click", tooltip.clickOutsideHandler);
      }
    }
  }
};

/**
 * Add PDF Tools FTE tooltip to the dropdown element
 */
var addPdfToolsFteTooltipToAttachmentDiv = function addPdfToolsFteTooltipToAttachmentDiv(pdfToolsDropdownElement) {
  var _state$gmailConfig, _state$gmailConfig2, _state$gmailConfig3;
  var tooltipStrings = {
    title: _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === null || _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === void 0 || (_state$gmailConfig = _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].gmailConfig) === null || _state$gmailConfig === void 0 || (_state$gmailConfig = _state$gmailConfig.pdfToolsFteToolTipStrings) === null || _state$gmailConfig === void 0 ? void 0 : _state$gmailConfig.title,
    description: _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === null || _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === void 0 || (_state$gmailConfig2 = _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].gmailConfig) === null || _state$gmailConfig2 === void 0 || (_state$gmailConfig2 = _state$gmailConfig2.pdfToolsFteToolTipStrings) === null || _state$gmailConfig2 === void 0 ? void 0 : _state$gmailConfig2.description,
    button: _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === null || _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === void 0 || (_state$gmailConfig3 = _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].gmailConfig) === null || _state$gmailConfig3 === void 0 || (_state$gmailConfig3 = _state$gmailConfig3.pdfToolsFteToolTipStrings) === null || _state$gmailConfig3 === void 0 ? void 0 : _state$gmailConfig3.button
  };
  var tooltip = (0,_utils_fte_utils_js__WEBPACK_IMPORTED_MODULE_3__.createFteTooltip)(tooltipStrings, "pdfTools");

  // Create bound function to enable proper removeEventListener
  function clickOutsideHandler(event) {
    handleFteClickOutside(event, tooltip);
  }
  tooltip.clickOutsideHandler = clickOutsideHandler;
  (0,_utils_fte_utils_js__WEBPACK_IMPORTED_MODULE_3__.addFteCloseButtonListener)(tooltip, {
    fteType: "pdfTools",
    onClose: function onClose() {
      _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].fteToolTip.eligibleFte.type = "";
      (0,_utils_util_js__WEBPACK_IMPORTED_MODULE_1__.sendAnalytics)([[DIRECT_VERB_FTE_DISMISSED_ANALYTICS_EVENT, {
        source: "gmail_chrome",
        workflow: "pdf_tools"
      }]]);
    },
    sendErrorLog: _utils_util_js__WEBPACK_IMPORTED_MODULE_1__.sendErrorLog
  });

  // Add event listener to the document to detect click outside
  document.addEventListener("click", clickOutsideHandler, {
    once: true,
    signal: _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === null || _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === void 0 ? void 0 : _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].eventControllerSignal
  });
  _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].fteToolTip.eligibleFte.type = "pdfTools";

  // IMPORTANT: Wait for React to render, then append tooltip
  var shadowRoot = pdfToolsDropdownElement.shadowRoot;
  if (!shadowRoot) {
    (0,_utils_util_js__WEBPACK_IMPORTED_MODULE_1__.sendErrorLog)("Add_PDFToolsFTE_NoShadowRoot", "Shadow root not found on pdfToolsDropdownElement");
    return;
  }

  // Add a slight delay to ensure React has finished rendering and DOM is updated
  setTimeout(function () {
    var _state$gmailConfig4;
    var reactRoot = shadowRoot.querySelector("#pdf-tools-react-root");
    var ctaButton = shadowRoot.querySelector(".cvPdfTools-pdf-entrypoint-button");
    if (!reactRoot || !ctaButton) {
      (0,_utils_util_js__WEBPACK_IMPORTED_MODULE_1__.sendErrorLog)("PDFToolsFTE_ReactElementsNotFound", "React root or CTA button not found in shadow DOM");
      return;
    }

    // Append tooltip to reactRoot
    // CSS handles all positioning: position (absolute), right (0), top (42px), arrow position (52px from right)
    reactRoot.appendChild(tooltip);

    // Add hover listener to CTA button to dismiss FTE when context menu opens
    var _handleCtaHover = function handleCtaHover() {
      tooltip.remove();
      _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].fteToolTip.eligibleFte.type = "";
      (0,_utils_util_js__WEBPACK_IMPORTED_MODULE_1__.sendAnalytics)([[DIRECT_VERB_FTE_DISMISSED_ANALYTICS_EVENT, {
        source: "gmail_chrome",
        workflow: "pdf_tools"
      }]]);
      // Remove using the stored handler reference
      if (tooltip.clickOutsideHandler) {
        document.removeEventListener("click", tooltip.clickOutsideHandler);
      }
      ctaButton.removeEventListener("mouseenter", _handleCtaHover);
    };
    ctaButton.addEventListener("mouseenter", _handleCtaHover, {
      once: true
    });

    // Send analytics
    (0,_utils_util_js__WEBPACK_IMPORTED_MODULE_1__.sendAnalytics)([["DCBrowserExt:DirectVerb:Fte:Shown", {
      source: "gmail_chrome",
      workflow: "pdf_tools"
    }]]);
    (0,_utils_fte_utils_js__WEBPACK_IMPORTED_MODULE_3__.updateFteToolTipCoolDown)(_state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === null || _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === void 0 || (_state$gmailConfig4 = _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].gmailConfig) === null || _state$gmailConfig4 === void 0 || (_state$gmailConfig4 = _state$gmailConfig4.fteConfig) === null || _state$gmailConfig4 === void 0 ? void 0 : _state$gmailConfig4.tooltip, PDF_TOOLS_FTE_TOOLTIP_STORAGE_KEY).then(function (fteState) {
      _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].fteToolTip = _objectSpread(_objectSpread({}, _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === null || _state_js__WEBPACK_IMPORTED_MODULE_0__["default"] === void 0 ? void 0 : _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].fteToolTip), fteState);
    });
  }, 50); // 50ms delay to ensure DOM is updated
};

/**
 * Check eligibility and add PDF Tools FTE tooltip if conditions are met
 */
var addPdfToolsFTETooltipIfEligible = /*#__PURE__*/function () {
  var _ref = _asyncToGenerator(/*#__PURE__*/_regenerator().m(function _callee(pdfToolsDropdownElement) {
    var fteConfig, _t;
    return _regenerator().w(function (_context) {
      while (1) switch (_context.n) {
        case 0:
          _context.n = 1;
          return initDcLocalStorage();
        case 1:
          _context.n = 2;
          return chrome.storage.local.get(PDF_TOOLS_FTE_TOOLTIP_STORAGE_KEY);
        case 2:
          _t = PDF_TOOLS_FTE_TOOLTIP_STORAGE_KEY;
          fteConfig = _context.v[_t];
          if (!((fteConfig === null || fteConfig === void 0 ? void 0 : fteConfig.count) >= 1)) {
            _context.n = 3;
            break;
          }
          // PDF tools FTE only shown once per user
          gmailPdfToolsFteCoachmark.setEligibility(false);
          return _context.a(2);
        case 3:
          gmailPdfToolsFteCoachmark.setEligibility(true, function () {
            addPdfToolsFteTooltipToAttachmentDiv(pdfToolsDropdownElement);
          });
          // Trigger ShowOneChild to render the first eligible FTE
          chrome.runtime.sendMessage({
            main_op: "reRenderShowOneChild"
          });
        case 4:
          return _context.a(2);
      }
    }, _callee);
  }));
  return function addPdfToolsFTETooltipIfEligible(_x) {
    return _ref.apply(this, arguments);
  };
}();

/**
 * Main export: Render PDF Tools dropdown in Gmail native viewer
 *
 * @param {string} urlForAttachment - Attachment URL
 * @param {string} attachmentName - Attachment file name
 * @param {Function} getFileDetailsElementInNativeViewer - Function to get file details element
 * @returns {Promise<void>}
 */
var renderPdfToolsDropdown = /*#__PURE__*/function () {
  var _ref2 = _asyncToGenerator(/*#__PURE__*/_regenerator().m(function _callee2(urlForAttachment, attachmentName, getFileDetailsElementInNativeViewer) {
    var _parentElement$childN;
    var parentElement;
    return _regenerator().w(function (_context2) {
      while (1) switch (_context2.n) {
        case 0:
          parentElement = (0,_util_js__WEBPACK_IMPORTED_MODULE_2__.getParentElementForNativeViewerPrompt)();
          if (!(parentElement && (parentElement === null || parentElement === void 0 || (_parentElement$childN = parentElement.childNodes) === null || _parentElement$childN === void 0 ? void 0 : _parentElement$childN.length) > 0)) {
            _context2.n = 1;
            break;
          }
          return _context2.a(2, __webpack_require__("./chrome/content_scripts/gmail lazy recursive referencedExports: default")(chrome.runtime.getURL("dist/PdfToolsDropdown.js")).then(function (module) {
            var pdfToolsDropdownManager = module["default"];
            return pdfToolsDropdownManager.render(function (intent) {
              // Handle PDF tool verb clicks
              var promotionSource = (0,_utils_util_js__WEBPACK_IMPORTED_MODULE_1__.buildAcrobatPromotionSource)("gmail_chrome", intent === "openInAcrobat" ? "native_view" : intent);
              var viewerURL = (0,_util_js__WEBPACK_IMPORTED_MODULE_2__.createURLForAttachment)(urlForAttachment, promotionSource, attachmentName, intent === "openInAcrobat" ? "preview" : intent);
              window.open(viewerURL, "_blank");
            }, "gmailNativeViewer");
          }).then(function (pdfDropdownElement) {
            parentElement.insertBefore(pdfDropdownElement, parentElement.childNodes[0]);
            _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].nativeViewerPromptState.nativeViewerAttachmentURL = urlForAttachment;
            _state_js__WEBPACK_IMPORTED_MODULE_0__["default"].nativeViewerPromptState.previousFileDetailsElement = getFileDetailsElementInNativeViewer();
            if (window.innerWidth > 1200) {
              addPdfToolsFTETooltipIfEligible(pdfDropdownElement);
            }
          })["catch"](function (e) {
            (0,_utils_util_js__WEBPACK_IMPORTED_MODULE_1__.sendErrorLog)("PDFTools_ReactRenderError", e.message);
            throw e; // Re-throw so parent can handle cleanup
          }));
        case 1:
          throw new Error("Parent element not found for PDF Tools dropdown");
        case 2:
          return _context2.a(2);
      }
    }, _callee2);
  }));
  return function renderPdfToolsDropdown(_x2, _x3, _x4) {
    return _ref2.apply(this, arguments);
  };
}();

/**
 * Remove/cleanup PDF Tools dropdown from native viewer
 * Properly unmounts React component and removes DOM element
 *
 * @returns {Promise<void>}
 */
var removePdfToolsDropdown = /*#__PURE__*/function () {
  var _ref3 = _asyncToGenerator(/*#__PURE__*/_regenerator().m(function _callee3() {
    var pdfToolsTouchPoint;
    return _regenerator().w(function (_context3) {
      while (1) switch (_context3.n) {
        case 0:
          pdfToolsTouchPoint = document.querySelector(".".concat(PDF_TOOLS_TOUCHPOINT_CLASS));
          if (!pdfToolsTouchPoint) {
            _context3.n = 1;
            break;
          }
          return _context3.a(2, __webpack_require__("./chrome/content_scripts/gmail lazy recursive referencedExports: default")(chrome.runtime.getURL("dist/PdfToolsDropdown.js")).then(function (module) {
            var pdfToolsDropdownManager = module["default"];
            // Only try to unmount if the manager has a shadow root (valid state)
            if (pdfToolsDropdownManager && pdfToolsDropdownManager.isRendered()) {
              pdfToolsDropdownManager.remove();
            }
          })["catch"](function () {
            // Import failed (e.g., extension context invalidated)
            // Element will be cleaned up in finally block
          })["finally"](function () {
            // Always ensure the DOM element is removed
            // This handles edge cases:
            // 1. Extension reloaded: module reconstructed, isRendered() returns false
            // 2. Import failed: dynamic import threw error
            // 3. Manager couldn't unmount: shadow root doesn't exist
            var element = document.querySelector(".".concat(PDF_TOOLS_TOUCHPOINT_CLASS));
            if (element && element.parentElement) {
              element.parentElement.removeChild(element);
            }
          }));
        case 1:
          return _context3.a(2, Promise.resolve());
      }
    }, _callee3);
  }));
  return function removePdfToolsDropdown() {
    return _ref3.apply(this, arguments);
  };
}();


/***/ })

};

//# sourceMappingURL=chrome_content_scripts_gmail_native-viewer-pdf-tools-module_js.js.map