

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

function fromString(param) {
  switch (param) {
    case "ml" :
    case "ocaml" :
        return /* OCaml */1;
    case "re" :
    case "reason" :
        return /* Reason */0;
    default:
      return /* Other */2;
  }
}

var Flavour = {
  toReadableString: toReadableString,
  fromString: fromString
};

function defaultValue_001(param) {
  return /* () */0;
}

function defaultValue_002(param, src) {
  return src;
}

var defaultValue = /* record */Caml_chrome_debugger.record([
    "flavour",
    "setFlavour",
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

function BeltDocsFlavour$Provider(Props) {
  var children = Props.children;
  var match = React.useState((function () {
          return /* Reason */0;
        }));
  var setFlavour = match[1];
  var flavour = match[0];
  return React.createElement(make, {
              value: /* record */Caml_chrome_debugger.record([
                  "flavour",
                  "setFlavour",
                  "refmt"
                ], [
                  flavour,
                  (function (flavour) {
                      return Curry._1(setFlavour, (function (param) {
                                    return flavour;
                                  }));
                    }),
                  (function (lang, src) {
                      var exampleFlavour = fromString(lang);
                      switch (exampleFlavour) {
                        case /* Reason */0 :
                            if (flavour !== 1) {
                              return src;
                            } else {
                              return Reason.printML(Reason.parseRE(src));
                            }
                        case /* OCaml */1 :
                            if (flavour !== 0) {
                              return src;
                            } else {
                              return Reason.printRE(Reason.parseML(src));
                            }
                        case /* Other */2 :
                            return src;
                        
                      }
                    })
                ]),
              children: children
            });
}

var Provider = {
  make: BeltDocsFlavour$Provider
};

export {
  Flavour ,
  defaultValue ,
  ctx ,
  ContextProvider ,
  useContext ,
  Provider ,
  
}
/* ctx Not a pure module */
