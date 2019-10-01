

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Reason from "reason";
import * as Caml_chrome_debugger from "bs-platform/lib/es6/caml_chrome_debugger.js";

function toReadableString(param) {
  switch (param) {
    case /* Reason */0 :
        return "RE";
    case /* OCaml */1 :
        return "ML";
    case /* Other */2 :
        return "Other";
    
  }
}

var Syntax = {
  toReadableString: toReadableString
};

function defaultValue_001(param) {
  return /* () */0;
}

function defaultValue_002(param, param$1, src) {
  return src;
}

var defaultValue = /* record */Caml_chrome_debugger.record([
    "syntax",
    "setSyntax",
    "refmt"
  ], [
    0,
    defaultValue_001,
    defaultValue_002
  ]);

var ctx = React.createContext(defaultValue);

var make = ctx.Provider;

var ContextProvider = {
  make: make
};

function useContext(param) {
  return React.useContext(ctx);
}

function BeltDocsSyntax$Provider(Props) {
  var children = Props.children;
  var match = React.useState((function () {
          return /* Reason */0;
        }));
  var setSyntax = match[1];
  var syntax = match[0];
  return React.createElement(make, {
              value: /* record */Caml_chrome_debugger.record([
                  "syntax",
                  "setSyntax",
                  "refmt"
                ], [
                  syntax,
                  (function (syntax) {
                      return Curry._1(setSyntax, (function (param) {
                                    return syntax;
                                  }));
                    }),
                  (function (lang, meta, src) {
                      var exit = 0;
                      switch (lang) {
                        case "ml" :
                        case "ocaml" :
                            exit = 2;
                            break;
                        case "re" :
                        case "reason" :
                            exit = 1;
                            break;
                        default:
                          return src;
                      }
                      switch (exit) {
                        case 1 :
                            if (meta !== undefined && meta === "sig") {
                              if (syntax !== 1) {
                                return src;
                              } else {
                                return Reason.printMLI(Reason.parseREI(src));
                              }
                            }
                            if (syntax !== 1) {
                              return src;
                            } else {
                              return Reason.printML(Reason.parseRE(src));
                            }
                        case 2 :
                            if (meta !== undefined && meta === "sig") {
                              if (syntax !== 0) {
                                return src;
                              } else {
                                return Reason.printREI(Reason.parseMLI(src));
                              }
                            }
                            if (syntax !== 0) {
                              return src;
                            } else {
                              return Reason.printREI(Reason.parseMLI(src));
                            }
                        
                      }
                    })
                ]),
              children: children
            });
}

var Provider = {
  make: BeltDocsSyntax$Provider
};

export {
  Syntax ,
  defaultValue ,
  ctx ,
  ContextProvider ,
  useContext ,
  Provider ,
  
}
/* ctx Not a pure module */
