

import * as Util from "../common/Util.bs.js";
import * as React from "react";
import * as BeltDocsSyntax from "../layouts/BeltDocsSyntax.bs.js";

function CodeExample(Props) {
  var children = Props.children;
  var syntax = Props.syntax;
  return React.createElement("div", {
              className: "flex flex-col rounded-lg bg-sand-lighten-20 py-4 px-6 mt-6"
            }, React.createElement("div", {
                  className: "flex justify-between font-overpass text-main-lighten-20 font-bold text-sm mb-3"
                }, Util.ReactStuff.s("Example"), React.createElement("span", {
                      className: "font-montserrat text-primary-lighten-50"
                    }, Util.ReactStuff.s(BeltDocsSyntax.Syntax.toReadableString(syntax)))), children);
}

var make = CodeExample;

export {
  make ,
  
}
/* react Not a pure module */
