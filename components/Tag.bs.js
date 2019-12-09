

import * as Util from "../common/Util.bs.js";
import * as React from "react";

function Tag(Props) {
  var children = Props.children;
  Props.kind;
  return React.createElement("div", {
              className: "px-2 inline-block align-bottom bg-snow-dark text-night font-semibold rounded text-sm"
            }, Util.ReactStuff.s(children));
}

var make = Tag;

export {
  make ,
  
}
/* react Not a pure module */
