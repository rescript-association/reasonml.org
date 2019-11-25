

import * as React from "react";
import * as Js_dict from "bs-platform/lib/es6/js_dict.js";
import * as ColorTheme from "../common/ColorTheme.bs.js";
import * as Navigation from "../components/Navigation.bs.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Router from "next/router";
import * as React$1 from "@mdx-js/react";
import * as SidebarLayout from "./SidebarLayout.bs.js";
import * as Caml_chrome_debugger from "bs-platform/lib/es6/caml_chrome_debugger.js";

require('../styles/main.css')
;


let hljs = require('highlight.js/lib/highlight');
let reasonHighlightJs = require('reason-highlightjs');
hljs.registerLanguage('reason', reasonHighlightJs);

;

var indexData = (require('../index_data/js_api_index.json'));

var $$package = (require('../package.json'));

var overviewNavs = /* array */[/* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Introduction",
      "/apis/javascript/latest/js"
    ])];

var apiNavs = /* array */[
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Array2",
      "/apis/javascript/latest/js/array-2"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Array",
      "/apis/javascript/latest/js/array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Console",
      "/apis/javascript/latest/js/console"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Date",
      "/apis/javascript/latest/js/date"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Dict",
      "/apis/javascript/latest/js/dict"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Exn",
      "/apis/javascript/latest/js/exn"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Float",
      "/apis/javascript/latest/js/float"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Global",
      "/apis/javascript/latest/js/global"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Int",
      "/apis/javascript/latest/js/int"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Json",
      "/apis/javascript/latest/js/json"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "List",
      "/apis/javascript/latest/js/list"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Math",
      "/apis/javascript/latest/js/math"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "NullUndefined",
      "/apis/javascript/latest/js/null-undefined"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Null",
      "/apis/javascript/latest/js/null"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Nullable",
      "/apis/javascript/latest/js/nullable"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Obj",
      "/apis/javascript/latest/js/obj"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Option",
      "/apis/javascript/latest/js/option"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Promise",
      "/apis/javascript/latest/js/promise"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Re",
      "/apis/javascript/latest/js/re"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Result",
      "/apis/javascript/latest/js/result"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "String2",
      "/apis/javascript/latest/js/string-2"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "String",
      "/apis/javascript/latest/js/string"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayArrayBuffer",
      "/apis/javascript/latest/js/typed-array_array-buffer"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayDataView",
      "/apis/javascript/latest/js/typed-array_data-view"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayFloat32Array",
      "/apis/javascript/latest/js/typed-array_float-32-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayFloat64Array",
      "/apis/javascript/latest/js/typed-array_float-64-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayInt8Array",
      "/apis/javascript/latest/js/typed-array_int-8-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayInt16Array",
      "/apis/javascript/latest/js/typed-array_int-16-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayInt32Array",
      "/apis/javascript/latest/js/typed-array_int-32-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayTypeS",
      "/apis/javascript/latest/js/typed-array_type-s"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayUint8Array",
      "/apis/javascript/latest/js/typed-array_uint-8-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayUint8ClampedArray",
      "/apis/javascript/latest/js/typed-array_uint-8-clamped-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayUint16Array",
      "/apis/javascript/latest/js/typed-array_uint-16-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArrayUint32Array",
      "/apis/javascript/latest/js/typed-array_uint-32-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2ArrayBuffer",
      "/apis/javascript/latest/js/typed-array-2_array-buffer"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2DataView",
      "/apis/javascript/latest/js/typed-array-2_data-view"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2Float32Array",
      "/apis/javascript/latest/js/typed-array-2_float-32-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2Float64Array",
      "/apis/javascript/latest/js/typed-array-2_float-64-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2Int8Array",
      "/apis/javascript/latest/js/typed-array-2_int-8-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2Int16Array",
      "/apis/javascript/latest/js/typed-array-2_int-16-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2Int32Array",
      "/apis/javascript/latest/js/typed-array-2_int-32-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2Uint8Array",
      "/apis/javascript/latest/js/typed-array-2_uint-8-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2Uint8ClampedArray",
      "/apis/javascript/latest/js/typed-array-2_uint-8-clamped-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2Uint16Array",
      "/apis/javascript/latest/js/typed-array-2_uint-16-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2Uint32Array",
      "/apis/javascript/latest/js/typed-array-2_uint-32-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray2",
      "/apis/javascript/latest/js/typed-array-2"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "TypedArray",
      "/apis/javascript/latest/js/typed-array"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Types",
      "/apis/javascript/latest/js/types"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Undefined",
      "/apis/javascript/latest/js/undefined"
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "href"
    ], [
      "Vector",
      "/apis/javascript/latest/js/vector"
    ])
];

var categories = /* array */[
  /* record */Caml_chrome_debugger.record([
      "name",
      "items"
    ], [
      "Overview",
      overviewNavs
    ]),
  /* record */Caml_chrome_debugger.record([
      "name",
      "items"
    ], [
      "API",
      apiNavs
    ])
];

function JsDocsLayout$Docs(Props) {
  var match = Props.components;
  var components = match !== undefined ? Caml_option.valFromOption(match) : SidebarLayout.ApiMd.components;
  var children = Props.children;
  var theme = ColorTheme.toCN(/* Js */16617);
  var router = Router.useRouter();
  var route = router.route;
  var headers = Belt_Option.getWithDefault(Belt_Option.map(Js_dict.get(indexData, route), (function (data) {
              return data.headers;
            })), /* array */[]);
  var moduleName = Belt_Option.getWithDefault(Belt_Option.map(Js_dict.get(indexData, route), (function (data) {
              return data.moduleName;
            })), "?");
  var match$1 = route !== "/apis/javascript/latest/js";
  var collapsibleSection = match$1 ? React.createElement(SidebarLayout.Sidebar.CollapsibleSection.make, {
          headers: headers,
          moduleName: moduleName
        }) : null;
  var minWidth = {
    minWidth: "20rem"
  };
  return React.createElement("div", undefined, React.createElement("div", {
                  className: "max-w-4xl w-full " + theme,
                  style: minWidth
                }, React.createElement(Navigation.ApiDocs.make, {
                      route: router.route,
                      versionInfo: "v" + $$package.dependencies["bs-platform"]
                    }), React.createElement("div", {
                      className: "flex mt-12"
                    }, React.createElement(SidebarLayout.Sidebar.make, {
                          categories: categories,
                          route: router.route,
                          children: collapsibleSection
                        }), React.createElement("main", {
                          className: "pt-12 w-4/5 static min-h-screen overflow-visible"
                        }, React.createElement(React$1.MDXProvider, {
                              components: components,
                              children: React.createElement("div", {
                                    className: "pl-8 max-w-md mb-32 text-lg"
                                  }, children)
                            })))));
}

var Docs = {
  make: JsDocsLayout$Docs
};

function JsDocsLayout$Prose(Props) {
  var children = Props.children;
  return React.createElement(JsDocsLayout$Docs, {
              components: SidebarLayout.ProseMd.components,
              children: children
            });
}

var Prose = {
  make: JsDocsLayout$Prose
};

var Link = 0;

var Sidebar = 0;

var NavItem = 0;

var Category = 0;

export {
  Link ,
  indexData ,
  $$package ,
  Sidebar ,
  NavItem ,
  Category ,
  overviewNavs ,
  apiNavs ,
  categories ,
  Docs ,
  Prose ,
  
}
/*  Not a pure module */
