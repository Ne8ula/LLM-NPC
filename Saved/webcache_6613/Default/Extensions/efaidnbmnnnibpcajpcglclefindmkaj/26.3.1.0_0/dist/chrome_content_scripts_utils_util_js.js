export const __webpack_esm_id__ = "chrome_content_scripts_utils_util_js";
export const __webpack_esm_ids__ = ["chrome_content_scripts_utils_util_js"];
export const __webpack_esm_modules__ = {

/***/ "./chrome/content_scripts/utils/util.js":
/*!**********************************************!*\
  !*** ./chrome/content_scripts/utils/util.js ***!
  \**********************************************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

__webpack_require__.r(__webpack_exports__);
/* harmony export */ __webpack_require__.d(__webpack_exports__, {
/* harmony export */   addFontToDocument: () => (/* binding */ addFontToDocument),
/* harmony export */   buildAcrobatPromotionSource: () => (/* binding */ buildAcrobatPromotionSource),
/* harmony export */   createAcrobatIconElement: () => (/* binding */ createAcrobatIconElement),
/* harmony export */   extractFileIdFromDriveUrl: () => (/* binding */ extractFileIdFromDriveUrl),
/* harmony export */   fetchDefaultViewershipConfig: () => (/* binding */ fetchDefaultViewershipConfig),
/* harmony export */   getClosestElementBySelectors: () => (/* binding */ getClosestElementBySelectors),
/* harmony export */   getDVSessionCountString: () => (/* binding */ getDVSessionCountString),
/* harmony export */   getElementFromParent: () => (/* binding */ getElementFromParent),
/* harmony export */   getElementListForSelectors: () => (/* binding */ getElementListForSelectors),
/* harmony export */   getElementsListBasedOnSelectors: () => (/* binding */ getElementsListBasedOnSelectors),
/* harmony export */   getFileDetails: () => (/* binding */ getFileDetails),
/* harmony export */   getFirstElementBasedOnSelectors: () => (/* binding */ getFirstElementBasedOnSelectors),
/* harmony export */   getParsedJSON: () => (/* binding */ getParsedJSON),
/* harmony export */   incrementDVSessionCount: () => (/* binding */ incrementDVSessionCount),
/* harmony export */   isAnalyticsSentInTheMonthOrSession: () => (/* binding */ isAnalyticsSentInTheMonthOrSession),
/* harmony export */   resetDVSessionCount: () => (/* binding */ resetDVSessionCount),
/* harmony export */   sendAnalytics: () => (/* binding */ sendAnalytics),
/* harmony export */   sendAnalyticsOnce: () => (/* binding */ sendAnalyticsOnce),
/* harmony export */   sendAnalyticsOncePerMonth: () => (/* binding */ sendAnalyticsOncePerMonth),
/* harmony export */   sendErrorLog: () => (/* binding */ sendErrorLog)
/* harmony export */ });
function _typeof(o) { "@babel/helpers - typeof"; return _typeof = "function" == typeof Symbol && "symbol" == typeof Symbol.iterator ? function (o) { return typeof o; } : function (o) { return o && "function" == typeof Symbol && o.constructor === Symbol && o !== Symbol.prototype ? "symbol" : typeof o; }, _typeof(o); }
function _createForOfIteratorHelper(r, e) { var t = "undefined" != typeof Symbol && r[Symbol.iterator] || r["@@iterator"]; if (!t) { if (Array.isArray(r) || (t = _unsupportedIterableToArray(r)) || e && r && "number" == typeof r.length) { t && (r = t); var _n = 0, F = function F() {}; return { s: F, n: function n() { return _n >= r.length ? { done: !0 } : { done: !1, value: r[_n++] }; }, e: function e(r) { throw r; }, f: F }; } throw new TypeError("Invalid attempt to iterate non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method."); } var o, a = !0, u = !1; return { s: function s() { t = t.call(r); }, n: function n() { var r = t.next(); return a = r.done, r; }, e: function e(r) { u = !0, o = r; }, f: function f() { try { a || null == t["return"] || t["return"](); } finally { if (u) throw o; } } }; }
function _unsupportedIterableToArray(r, a) { if (r) { if ("string" == typeof r) return _arrayLikeToArray(r, a); var t = {}.toString.call(r).slice(8, -1); return "Object" === t && r.constructor && (t = r.constructor.name), "Map" === t || "Set" === t ? Array.from(r) : "Arguments" === t || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(t) ? _arrayLikeToArray(r, a) : void 0; } }
function _arrayLikeToArray(r, a) { (null == a || a > r.length) && (a = r.length); for (var e = 0, n = Array(a); e < a; e++) n[e] = r[e]; return n; }
function _regenerator() { /*! regenerator-runtime -- Copyright (c) 2014-present, Facebook, Inc. -- license (MIT): https://github.com/babel/babel/blob/main/packages/babel-helpers/LICENSE */ var e, t, r = "function" == typeof Symbol ? Symbol : {}, n = r.iterator || "@@iterator", o = r.toStringTag || "@@toStringTag"; function i(r, n, o, i) { var c = n && n.prototype instanceof Generator ? n : Generator, u = Object.create(c.prototype); return _regeneratorDefine2(u, "_invoke", function (r, n, o) { var i, c, u, f = 0, p = o || [], y = !1, G = { p: 0, n: 0, v: e, a: d, f: d.bind(e, 4), d: function d(t, r) { return i = t, c = 0, u = e, G.n = r, a; } }; function d(r, n) { for (c = r, u = n, t = 0; !y && f && !o && t < p.length; t++) { var o, i = p[t], d = G.p, l = i[2]; r > 3 ? (o = l === n) && (u = i[(c = i[4]) ? 5 : (c = 3, 3)], i[4] = i[5] = e) : i[0] <= d && ((o = r < 2 && d < i[1]) ? (c = 0, G.v = n, G.n = i[1]) : d < l && (o = r < 3 || i[0] > n || n > l) && (i[4] = r, i[5] = n, G.n = l, c = 0)); } if (o || r > 1) return a; throw y = !0, n; } return function (o, p, l) { if (f > 1) throw TypeError("Generator is already running"); for (y && 1 === p && d(p, l), c = p, u = l; (t = c < 2 ? e : u) || !y;) { i || (c ? c < 3 ? (c > 1 && (G.n = -1), d(c, u)) : G.n = u : G.v = u); try { if (f = 2, i) { if (c || (o = "next"), t = i[o]) { if (!(t = t.call(i, u))) throw TypeError("iterator result is not an object"); if (!t.done) return t; u = t.value, c < 2 && (c = 0); } else 1 === c && (t = i["return"]) && t.call(i), c < 2 && (u = TypeError("The iterator does not provide a '" + o + "' method"), c = 1); i = e; } else if ((t = (y = G.n < 0) ? u : r.call(n, G)) !== a) break; } catch (t) { i = e, c = 1, u = t; } finally { f = 1; } } return { value: t, done: y }; }; }(r, o, i), !0), u; } var a = {}; function Generator() {} function GeneratorFunction() {} function GeneratorFunctionPrototype() {} t = Object.getPrototypeOf; var c = [][n] ? t(t([][n]())) : (_regeneratorDefine2(t = {}, n, function () { return this; }), t), u = GeneratorFunctionPrototype.prototype = Generator.prototype = Object.create(c); function f(e) { return Object.setPrototypeOf ? Object.setPrototypeOf(e, GeneratorFunctionPrototype) : (e.__proto__ = GeneratorFunctionPrototype, _regeneratorDefine2(e, o, "GeneratorFunction")), e.prototype = Object.create(u), e; } return GeneratorFunction.prototype = GeneratorFunctionPrototype, _regeneratorDefine2(u, "constructor", GeneratorFunctionPrototype), _regeneratorDefine2(GeneratorFunctionPrototype, "constructor", GeneratorFunction), GeneratorFunction.displayName = "GeneratorFunction", _regeneratorDefine2(GeneratorFunctionPrototype, o, "GeneratorFunction"), _regeneratorDefine2(u), _regeneratorDefine2(u, o, "Generator"), _regeneratorDefine2(u, n, function () { return this; }), _regeneratorDefine2(u, "toString", function () { return "[object Generator]"; }), (_regenerator = function _regenerator() { return { w: i, m: f }; })(); }
function _regeneratorDefine2(e, r, n, t) { var i = Object.defineProperty; try { i({}, "", {}); } catch (e) { i = 0; } _regeneratorDefine2 = function _regeneratorDefine(e, r, n, t) { function o(r, n) { _regeneratorDefine2(e, r, function (e) { return this._invoke(r, n, e); }); } r ? i ? i(e, r, { value: n, enumerable: !t, configurable: !t, writable: !t }) : e[r] = n : (o("next", 0), o("throw", 1), o("return", 2)); }, _regeneratorDefine2(e, r, n, t); }
function _defineProperty(e, r, t) { return (r = _toPropertyKey(r)) in e ? Object.defineProperty(e, r, { value: t, enumerable: !0, configurable: !0, writable: !0 }) : e[r] = t, e; }
function _toPropertyKey(t) { var i = _toPrimitive(t, "string"); return "symbol" == _typeof(i) ? i : i + ""; }
function _toPrimitive(t, r) { if ("object" != _typeof(t) || !t) return t; var e = t[Symbol.toPrimitive]; if (void 0 !== e) { var i = e.call(t, r || "default"); if ("object" != _typeof(i)) return i; throw new TypeError("@@toPrimitive must return a primitive value."); } return ("string" === r ? String : Number)(t); }
function asyncGeneratorStep(n, t, e, r, o, a, c) { try { var i = n[a](c), u = i.value; } catch (n) { return void e(n); } i.done ? t(u) : Promise.resolve(u).then(r, o); }
function _asyncToGenerator(n) { return function () { var t = this, e = arguments; return new Promise(function (r, o) { var a = n.apply(t, e); function _next(n) { asyncGeneratorStep(a, r, o, _next, _throw, "next", n); } function _throw(n) { asyncGeneratorStep(a, r, o, _next, _throw, "throw", n); } _next(void 0); }); }; }
/*************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 *  Copyright 2024 Adobe Systems Incorporated
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

var sendAnalytics = function sendAnalytics(analytics) {
  try {
    chrome.runtime.sendMessage({
      main_op: "analytics",
      analytics: analytics
    });
  } catch (e) {
    // genuine error may come when extension context is invalidated
  }
};

// returns date in yyyyMM format
var formatDateForMonthlyAnalyticsEvent = function formatDateForMonthlyAnalyticsEvent(todayDate) {
  if (todayDate instanceof Date) {
    return "".concat(todayDate.getUTCFullYear()).concat((todayDate.getUTCMonth() + 1).toString().padStart(2, "0"));
  }
  return "";
};
var eventsSent = new Set();
var sendAnalyticsOnce = function sendAnalyticsOnce(eventString) {
  if (!(eventsSent !== null && eventsSent !== void 0 && eventsSent.has(eventString))) {
    eventsSent.add(eventString);
    sendAnalyticsEvent([eventString]);
  }
};
var analyticsEvents = new Map();
/**
 * Send analytics event once per month
 * * Checks object in session storage if flag is already sent for the month
 * * Checks local storage for cross tab event status
 * @param eventString
 * @param options
 * @returns {Promise<void>}
 */
var sendAnalyticsOncePerMonth = /*#__PURE__*/function () {
  var _ref = _asyncToGenerator(/*#__PURE__*/_regenerator().m(function _callee(eventString, options) {
    var _eventDetails$eventSt, todayDate, currentYearMonth, eventDetails, lastSentYearMonth, analyticsPayload, eventDetailsToSave, _t;
    return _regenerator().w(function (_context) {
      while (1) switch (_context.p = _context.n) {
        case 0:
          if (!eventString) {
            _context.n = 5;
            break;
          }
          _context.p = 1;
          if (analyticsEvents !== null && analyticsEvents !== void 0 && analyticsEvents.has(eventString)) {
            _context.n = 3;
            break;
          }
          todayDate = new Date();
          currentYearMonth = formatDateForMonthlyAnalyticsEvent(todayDate);
          analyticsEvents.set(eventString, currentYearMonth);
          _context.n = 2;
          return chrome.storage.local.get([eventString]);
        case 2:
          eventDetails = _context.v;
          lastSentYearMonth = eventDetails === null || eventDetails === void 0 || (_eventDetails$eventSt = eventDetails[eventString]) === null || _eventDetails$eventSt === void 0 ? void 0 : _eventDetails$eventSt.lastSentYearMonth; //only send analytics if it's not sent in this month
          if (!lastSentYearMonth || currentYearMonth > lastSentYearMonth) {
            analyticsPayload = options ? [[eventString, options]] : [eventString];
            sendAnalytics(analyticsPayload);
            // add to map with date
            eventDetailsToSave = {
              "lastSentYearMonth": currentYearMonth
            };
            chrome.storage.local.set(_defineProperty({}, eventString, eventDetailsToSave));
          }
        case 3:
          _context.n = 5;
          break;
        case 4:
          _context.p = 4;
          _t = _context.v;
        case 5:
          return _context.a(2);
      }
    }, _callee, null, [[1, 4]]);
  }));
  return function sendAnalyticsOncePerMonth(_x, _x2) {
    return _ref.apply(this, arguments);
  };
}();

// Gsuite default viewership related methods starts here.
var getDVSessionCountStorageKey = function getDVSessionCountStorageKey(surfaceId) {
  return "".concat(surfaceId, "-pdf-default-viewership-session-count");
};
var getDVStorageKey = function getDVStorageKey(surfaceId) {
  return "".concat(surfaceId, "-pdf-default-viewership");
};
var resetDVSessionCount = function resetDVSessionCount(surfaceId) {
  chrome.storage.local.set(_defineProperty({}, getDVSessionCountStorageKey(surfaceId), 0));
};
var incrementDVSessionCount = function incrementDVSessionCount(surfaceId) {
  getDVSessionCount(surfaceId).then(function (sessionCount) {
    chrome.storage.local.set(_defineProperty({}, getDVSessionCountStorageKey(surfaceId), sessionCount + 1));
  });
};
var getDVSessionCount = function getDVSessionCount(surfaceId) {
  return chrome.storage.local.get(getDVSessionCountStorageKey(surfaceId)).then(function (res) {
    return (res === null || res === void 0 ? void 0 : res[getDVSessionCountStorageKey(surfaceId)]) || 0;
  });
};
var getDVSessionCountString = function getDVSessionCountString(surfaceId) {
  return getDVSessionCount(surfaceId).then(function (sessionCount) {
    if (sessionCount < 3) {
      return sessionCount.toString();
    }
    return "3_or_more";
  });
};
var fetchDefaultViewershipConfig = /*#__PURE__*/function () {
  var _ref2 = _asyncToGenerator(/*#__PURE__*/_regenerator().m(function _callee2(surfaceId) {
    var _yield$chrome$storage;
    var _t2, _t3, _t4, _t5;
    return _regenerator().w(function (_context2) {
      while (1) switch (_context2.n) {
        case 0:
          _context2.n = 1;
          return chrome.storage.local.get(getDVStorageKey(surfaceId));
        case 1:
          _t4 = _yield$chrome$storage = _context2.v;
          _t3 = _t4 === null;
          if (_t3) {
            _context2.n = 2;
            break;
          }
          _t3 = _yield$chrome$storage === void 0;
        case 2:
          if (!_t3) {
            _context2.n = 3;
            break;
          }
          _t5 = void 0;
          _context2.n = 4;
          break;
        case 3:
          _t5 = _yield$chrome$storage[getDVStorageKey(surfaceId)];
        case 4:
          _t2 = _t5;
          if (_t2) {
            _context2.n = 5;
            break;
          }
          _t2 = {};
        case 5:
          return _context2.a(2, _t2);
      }
    }, _callee2);
  }));
  return function fetchDefaultViewershipConfig(_x3) {
    return _ref2.apply(this, arguments);
  };
}();
// Gsuite default viewership related methods ends here.

/**
 * Create Acrobat icon element
 * @returns {HTMLImageElement}
 */
var createAcrobatIconElement = function createAcrobatIconElement(className, iconPath) {
  var acrobatImage = document.createElement("img");
  var iconUrl = chrome.runtime.getURL(iconPath);
  acrobatImage.setAttribute("src", iconUrl);
  acrobatImage.setAttribute("class", className);
  return acrobatImage;
};
var isAnalyticsSentInTheMonthOrSession = function isAnalyticsSentInTheMonthOrSession(eventString) {
  return analyticsEvents === null || analyticsEvents === void 0 ? void 0 : analyticsEvents.has(eventString);
};
var sendErrorLog = function sendErrorLog(message, error) {
  chrome.runtime.sendMessage({
    main_op: "log-error",
    log: {
      message: message,
      error: error
    }
  });
};
var getParsedJSON = function getParsedJSON(input) {
  var parsedJSON;
  try {
    parsedJSON = JSON.parse(input);
  } catch (e) {}
  return parsedJSON;
};
var extractFileIdFromDriveUrl = function extractFileIdFromDriveUrl(url) {
  var fileId = "";
  if (!url) {
    return fileId;
  }
  try {
    var decodedUrl = decodeURIComponent(url);

    // Case 1: Google Drive links (either `/file/d/` or `/open?id=`)
    if (decodedUrl.startsWith("https://drive.google.com/") || decodedUrl.startsWith("https://docs.google.com/file")) {
      fileId = decodedUrl.split('/')[5] || new URL(decodedUrl).searchParams.get("id");
    }
    // Case 2: Gmail URL with "q" as parameter pointing to a Google Doc
    else if (decodedUrl.startsWith("https://www.google.com/url")) {
      var parsedUrl = new URL(decodedUrl);
      var targetUrl = parsedUrl.searchParams.get('q');
      if (targetUrl) {
        var documentUrl = new URL(targetUrl);
        fileId = documentUrl.pathname.split('/')[3];
      }
    }
  } catch (e) {
    sendErrorLog("Error in GSuite", "Error in extracting file ID from URL");
  }
  return fileId;
};

/**
 * Get elements list in DOM for passed selectors.
 * @param selectors - array of selectors ["a","b"]
 * @param parentElement - parent element to search for selectors
 * @returns {*[]} - array of div elements for the selectors present in the DOM
 */
var getElementListForSelectors = function getElementListForSelectors() {
  var selectors = arguments.length > 0 && arguments[0] !== undefined ? arguments[0] : [];
  var parentElement = arguments.length > 1 && arguments[1] !== undefined ? arguments[1] : null;
  var elementList = new Set();
  var parent = parentElement || document;
  var _iterator = _createForOfIteratorHelper(selectors),
    _step;
  try {
    for (_iterator.s(); !(_step = _iterator.n()).done;) {
      var selector = _step.value;
      var elements = parent.getElementsByClassName(selector);
      if ((elements === null || elements === void 0 ? void 0 : elements.length) > 0) {
        var divList = Array.from(elements);
        divList === null || divList === void 0 || divList.forEach(function (div) {
          return elementList.add(div);
        });
      }
    }
  } catch (err) {
    _iterator.e(err);
  } finally {
    _iterator.f();
  }
  return Array.from(elementList);
};

/**
 * Get file details after parsing the file details element
 * @param {Element} fileDetailsElement - The file details element
 * @returns {Object} - The file details object
 */
var getFileDetails = function getFileDetails(fileDetailsElement) {
  try {
    var _fileDetailsElement$t;
    return JSON.parse(fileDetailsElement === null || fileDetailsElement === void 0 || (_fileDetailsElement$t = fileDetailsElement.textContent) === null || _fileDetailsElement$t === void 0 ? void 0 : _fileDetailsElement$t.replace(/\\/g, ""));
  } catch (ex) {
    return null;
  }
};

/**
 * Returns the first matching child element from the given parent element based on the provided selectors.
 * 
 * @param {string[]} selectors - An array of class names or CSS selectors to match against.
 * @param {Element|null} parentElement - The parent DOM element to search within. If null, the document is used.
 * @returns {Element|null} - The first matching element if found, otherwise null.
 */
var getElementFromParent = function getElementFromParent(selectors, parentElement) {
  var childElements = getElementListForSelectors(selectors, parentElement);
  return childElements.length > 0 ? childElements[0] : null;
};

/**
 * Returns an array of elements matching any of the given selectors within the specified root element.
 *
 * @param {string[]} elementSelectors - An array of CSS selector strings used to match elements.
 * @param {Element|null} rootElement - The root DOM element within which to search.
 * @returns {Element[]|null} - An array of matching elements if found, otherwise null.
 */
var getElementsListBasedOnSelectors = function getElementsListBasedOnSelectors() {
  var elementSelectors = arguments.length > 0 && arguments[0] !== undefined ? arguments[0] : [];
  var rootElement = arguments.length > 1 && arguments[1] !== undefined ? arguments[1] : null;
  if (!rootElement || !Array.isArray(elementSelectors) || elementSelectors.length === 0) {
    return null;
  }
  var matchedElements = new Set();
  var _iterator2 = _createForOfIteratorHelper(elementSelectors),
    _step2;
  try {
    for (_iterator2.s(); !(_step2 = _iterator2.n()).done;) {
      var selector = _step2.value;
      var elements = rootElement.querySelectorAll(selector);
      elements.forEach(function (el) {
        return matchedElements.add(el);
      });
    }
  } catch (err) {
    _iterator2.e(err);
  } finally {
    _iterator2.f();
  }
  return matchedElements.size > 0 ? Array.from(matchedElements) : null;
};

/**
 * Returns the first element matching any of the given selectors within the specified root element.
 *
 * @param {string[]} elementSelectors - An array of CSS selector strings used to match elements.
 * @param {Element|null} rootElement - The root DOM element within which to search.
 * @returns {Element|null} - The first matching element if found, otherwise null.
 */
var getFirstElementBasedOnSelectors = function getFirstElementBasedOnSelectors() {
  var elementSelectors = arguments.length > 0 && arguments[0] !== undefined ? arguments[0] : [];
  var rootElement = arguments.length > 1 && arguments[1] !== undefined ? arguments[1] : null;
  if (!rootElement || !Array.isArray(elementSelectors) || elementSelectors.length === 0) {
    return null;
  }
  var _iterator3 = _createForOfIteratorHelper(elementSelectors),
    _step3;
  try {
    for (_iterator3.s(); !(_step3 = _iterator3.n()).done;) {
      var selector = _step3.value;
      var element = rootElement.querySelector(selector);
      if (element) {
        return element; // Return the first matched element
      }
    }
  } catch (err) {
    _iterator3.e(err);
  } finally {
    _iterator3.f();
  }
  return null;
};

/**
 * Finds the closest ancestor matching any selector from the list.
 * @param {Element} element - Element to start from.
 * @param {string[]} [selectorsList=[]] - List of class names.
 * @returns {Element|null} Closest matching ancestor or null.
 */
var getClosestElementBySelectors = function getClosestElementBySelectors() {
  var element = arguments.length > 0 && arguments[0] !== undefined ? arguments[0] : null;
  var selectorsList = arguments.length > 1 && arguments[1] !== undefined ? arguments[1] : [];
  if (!element || !Array.isArray(selectorsList) || selectorsList.length === 0) {
    return null;
  }
  var _iterator4 = _createForOfIteratorHelper(selectorsList),
    _step4;
  try {
    for (_iterator4.s(); !(_step4 = _iterator4.n()).done;) {
      var selector = _step4.value;
      var containerElement = element.closest(selector);
      if (containerElement) return containerElement;
    }
  } catch (err) {
    _iterator4.e(err);
  } finally {
    _iterator4.f();
  }
  return null;
};

/**
 * The returned string is used to pass xId and xLocation in the iframe url
 * The logic to parse and set the iframe url is written in index.js
 * */
var buildAcrobatPromotionSource = function buildAcrobatPromotionSource(surface, surfaceLocation, suffix) {
  if (surface && surfaceLocation) {
    if (suffix) {
      return "".concat(surface, "-").concat(surfaceLocation, "-").concat(suffix);
    }
    return "".concat(surface, "-").concat(surfaceLocation);
  }
  return "";
};

/**
 * Loads Adobe Clean font for content script usage
 * @param {Object} state - State object to track font loading status
 * @returns {void}
 */
var addFontToDocument = function addFontToDocument(state) {
  if (!(state !== null && state !== void 0 && state.adobeCleanFontAdded)) {
    // load and add the font (if we add the touch point and then load the font, it may re-render text and cause a page reflow)
    var fontURL = chrome.runtime.getURL("browser/css/fonts/AdobeClean-Regular.otf");
    var fontFace = new FontFace("AdobeClean-Regular", "url(".concat(fontURL, ")"));
    fontFace.load().then(function () {
      document.fonts.add(fontFace);
    });
    state.adobeCleanFontAdded = true;
  }
};


/***/ })

};

//# sourceMappingURL=chrome_content_scripts_utils_util_js.js.map