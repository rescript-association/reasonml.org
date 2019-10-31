

import * as React from "react";

function Caret(Props) {
  var direction = Props.direction;
  return React.createElement("svg", {
              className: "stroke-current",
              viewBox: "0 0 14.5 7.1",
              x: "0px",
              y: "0px"
            }, direction >= 759637122 ? React.createElement("path", {
                    d: "M13.8,1.1L7.2,5.6L0.8,1.1",
                    fill: "none",
                    strokeWidth: "2.5"
                  }) : React.createElement("path", {
                    d: "M0.7,6.1l6.5-4.5l6.5,4.5",
                    fill: "none",
                    strokeWidth: "2.5"
                  }));
}

var make = Caret;

export {
  make ,
  
}
/* react Not a pure module */
