

import * as React from "react";
import * as ColorTheme from "../common/ColorTheme.bs.js";
import * as Navigation from "../components/Navigation.bs.js";
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

function JavaScriptApiLayout$Docs(Props) {
  var match = Props.theme;
  var theme = match !== undefined ? match : /* Reason */825328612;
  var match$1 = Props.components;
  var components = match$1 !== undefined ? Caml_option.valFromOption(match$1) : SidebarLayout.ApiMd.components;
  var children = Props.children;
  var router = Router.useRouter();
  var categories = /* array */[
    /* record */Caml_chrome_debugger.record([
        "name",
        "items"
      ], [
        "Introduction",
        [/* record */Caml_chrome_debugger.record([
              "name",
              "href"
            ], [
              "Overview",
              "/api"
            ])]
      ]),
    /* record */Caml_chrome_debugger.record([
        "name",
        "items"
      ], [
        "JavaScript",
        [
          /* record */Caml_chrome_debugger.record([
              "name",
              "href"
            ], [
              "Js Module",
              "/js_docs"
            ]),
          /* record */Caml_chrome_debugger.record([
              "name",
              "href"
            ], [
              "Belt Stdlib",
              "/belt_docs"
            ])
        ]
      ])
  ];
  var theme$1 = ColorTheme.toCN(theme);
  var minWidth = {
    minWidth: "20rem"
  };
  return React.createElement("div", undefined, React.createElement("div", {
                  className: "text-night max-w-4xl w-full " + theme$1,
                  style: minWidth
                }, React.createElement(Navigation.ApiDocs.make, {
                      route: router.route
                    }), React.createElement("div", {
                      className: "flex"
                    }, React.createElement(SidebarLayout.Sidebar.make, {
                          categories: categories,
                          route: router.route
                        }), React.createElement("main", {
                          className: "pt-12 static min-h-screen overflow-visible"
                        }, React.createElement(React$1.MDXProvider, {
                              components: components,
                              children: React.createElement("div", {
                                    className: "pl-8 max-w-md mb-32 text-lg"
                                  }, children)
                            })))));
}

var Docs = {
  make: JavaScriptApiLayout$Docs
};

function JavaScriptApiLayout$Prose(Props) {
  var children = Props.children;
  return React.createElement(JavaScriptApiLayout$Docs, {
              components: SidebarLayout.ProseMd.components,
              children: children
            });
}

var Prose = {
  make: JavaScriptApiLayout$Prose
};

var Link = 0;

var Sidebar = 0;

var ApiMd = 0;

export {
  Link ,
  Sidebar ,
  ApiMd ,
  Docs ,
  Prose ,
  
}
/*  Not a pure module */
