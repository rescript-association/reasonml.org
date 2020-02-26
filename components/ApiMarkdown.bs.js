

import * as React from "react";
import * as Markdown from "./Markdown.bs.js";

function ApiMarkdown$InvisibleAnchor(Props) {
  var id = Props.id;
  var style = {
    position: "absolute",
    top: "-1rem"
  };
  return React.createElement("span", {
              "aria-hidden": true,
              className: "relative"
            }, React.createElement("a", {
                  id: id,
                  style: style
                }));
}

var InvisibleAnchor = {
  make: ApiMarkdown$InvisibleAnchor
};

function ApiMarkdown$H1(Props) {
  var children = Props.children;
  return React.createElement("h1", {
              className: "text-6xl leading-1 mb-2 font-sans font-medium text-night-dark"
            }, children);
}

var H1 = {
  make: ApiMarkdown$H1
};

function ApiMarkdown$H2(Props) {
  var id = Props.id;
  Props.children;
  return React.createElement(React.Fragment, undefined, React.createElement(ApiMarkdown$InvisibleAnchor, {
                  id: id
                }), React.createElement("div", {
                  className: "border-b border-gray-200 my-20"
                }));
}

var H2 = {
  make: ApiMarkdown$H2
};

var $$default = {
  Intro: Markdown.Intro.make,
  p: Markdown.P.make,
  li: Markdown.Li.make,
  h1: ApiMarkdown$H1,
  h2: ApiMarkdown$H2,
  h3: Markdown.H3.make,
  h4: Markdown.H4.make,
  h5: Markdown.H5.make,
  ul: Markdown.Ul.make,
  ol: Markdown.Ol.make,
  thead: Markdown.Thead.make,
  th: Markdown.Th.make,
  td: Markdown.Td.make,
  inlineCode: Markdown.InlineCode.make,
  code: Markdown.Code.make,
  pre: Markdown.Pre.make,
  a: Markdown.A.make
};

export {
  InvisibleAnchor ,
  H1 ,
  H2 ,
  $$default ,
  $$default as default,
  
}
/* react Not a pure module */
