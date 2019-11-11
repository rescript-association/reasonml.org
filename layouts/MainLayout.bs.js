

import * as Mdx from "../common/Mdx.bs.js";
import * as Meta from "../components/Meta.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Navigation from "../components/Navigation.bs.js";
import * as Router from "next/router";
import * as React$1 from "@mdx-js/react";

require('../styles/main.css')
;

function MainLayout(Props) {
  var children = Props.children;
  var router = Router.useRouter();
  var minWidth = {
    minWidth: "20rem"
  };
  var match = React.useState((function () {
          return false;
        }));
  var setIsOpen = match[1];
  var isOpen = match[0];
  return React.createElement(React.Fragment, undefined, React.createElement(Meta.make, { }), React.createElement("div", {
                  className: "mb-32"
                }, React.createElement("div", {
                      className: "max-w-4xl w-full lg:w-3/4 text-night font-base"
                    }, React.createElement(Navigation.make, {
                          isOpen: isOpen,
                          toggle: (function (param) {
                              return Curry._1(setIsOpen, (function (prev) {
                                            return !prev;
                                          }));
                            }),
                          route: router.route
                        }), React.createElement("main", {
                          className: "mt-24 mx-4 max-w-lg" + (
                            isOpen ? " hidden" : ""
                          ),
                          style: minWidth
                        }, React.createElement(React$1.MDXProvider, {
                              components: Mdx.Components.$$default,
                              children: children
                            })))));
}

var Link = 0;

var make = MainLayout;

export {
  Link ,
  make ,
  
}
/*  Not a pure module */
