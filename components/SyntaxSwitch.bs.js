

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as BeltDocsSyntax from "../layouts/BeltDocsSyntax.bs.js";

function SyntaxSwitch(Props) {
  var syntaxContext = BeltDocsSyntax.useContext(/* () */0);
  var match = syntaxContext[/* syntax */0] === /* Reason */0;
  var match$1 = syntaxContext[/* syntax */0] === /* OCaml */1;
  return React.createElement("div", {
              className: "flex justify-between ml-4 border border-white rounded shadow"
            }, React.createElement("span", {
                  className: "p-2 " + (
                    match ? "bg-white text-black" : "text-white"
                  ),
                  onClick: (function (param) {
                      return Curry._1(syntaxContext[/* setSyntax */1], /* Reason */0);
                    })
                }, "Reason"), React.createElement("span", {
                  className: "p-2 " + (
                    match$1 ? "bg-white text-black" : "text-white"
                  ),
                  onClick: (function (param) {
                      return Curry._1(syntaxContext[/* setSyntax */1], /* OCaml */1);
                    })
                }, "OCaml"));
}

var make = SyntaxSwitch;

export {
  make ,
  
}
/* react Not a pure module */
