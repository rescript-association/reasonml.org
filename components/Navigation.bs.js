

import * as Icon from "./Icon.bs.js";
import * as Util from "../common/Util.bs.js";
import * as Caret from "./Caret.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Link from "next/link";

var link = "no-underline block text-inherit hover:text-white text-white-80";

var activeLink = "text-inherit font-bold text-fire-80 border-b border-fire-80";

function linkOrActiveLink(target, route) {
  var match = target === route;
  if (match) {
    return activeLink;
  } else {
    return link;
  }
}

function Navigation$CollapsibleLink(Props) {
  var title = Props.title;
  var route = Props.route;
  var href = Props.href;
  var children = Props.children;
  var match = React.useState((function () {
          return false;
        }));
  var setOpen = match[1];
  var isOpen = match[0];
  var onClick = function (param) {
    return Curry._1(setOpen, (function (prev) {
                  return !prev;
                }));
  };
  var direction = isOpen ? /* Up */19067 : /* Down */759637122;
  return React.createElement("div", {
              className: "font-bold sm:font-normal relative"
            }, React.createElement("div", {
                  className: "flex items-center"
                }, React.createElement(Link.default, {
                      href: href,
                      children: React.createElement("a", {
                            className: linkOrActiveLink(href, route) + " font-bold"
                          }, Util.ReactStuff.s(title))
                    }), React.createElement("div", {
                      className: "hover:cursor-pointer hover:text-white ml-2 w-3 h-2",
                      onClick: onClick
                    }, React.createElement(Caret.make, {
                          direction: direction
                        }))), React.createElement("div", {
                  className: (
                    isOpen ? "block" : "hidden"
                  ) + " sm:fixed sm:left-0 sm:border-night sm:border-t sm:mt-5 bg-night-dark w-full"
                }, children));
}

var CollapsibleLink = {
  make: Navigation$CollapsibleLink
};

function Navigation(Props) {
  var match = Props.isOpen;
  var isOpen = match !== undefined ? match : false;
  var match$1 = Props.toggle;
  var toggle = match$1 !== undefined ? match$1 : (function (param) {
        return /* () */0;
      });
  var match$2 = Props.route;
  var route = match$2 !== undefined ? match$2 : "/";
  var minWidth = "20rem";
  return React.createElement("nav", {
              className: "fixed z-10 top-0 sm:pl-10 w-full h-16 bg-night-dark shadow text-white-80 text-xl sm:text-base",
              id: "header",
              style: {
                minWidth: minWidth
              }
            }, React.createElement("div", {
                  className: "flex justify-between sm:items-center h-full"
                }, React.createElement(Link.default, {
                      href: "/",
                      children: React.createElement("a", {
                            className: "w-24 sm:mb-4"
                          }, React.createElement("img", {
                                src: "/static/reason_logo.svg"
                              }))
                    }), React.createElement("div", {
                      className: "block sm:hidden"
                    }, React.createElement("button", {
                          className: "flex items-center px-3 py-2 border rounded text-teal-200 border-teal-400 hover:text-white hover:border-white",
                          onClick: (function (param) {
                              return Curry._1(toggle, /* () */0);
                            })
                        }, React.createElement("svg", {
                              className: "fill-current h-3 w-3",
                              viewBox: "0 0 20 20",
                              xmlns: "http://www.w3.org/2000/svg"
                            }, React.createElement("path", {
                                  d: "M0 3h20v2H0V3zm0 6h20v2H0V9zm0 6h20v2H0v-2z"
                                })))), React.createElement("div", {
                      className: (
                        isOpen ? "flex" : "hidden"
                      ) + " px-2 flex-col fixed top-0 left-0 h-full w-full bg-night-dark sm:pl-10 sm:h-auto sm:flex sm:relative sm:flex-row sm:justify-between",
                      style: {
                        minWidth: minWidth
                      }
                    }, React.createElement("div", {
                          className: "flex h-16 justify-between items-center sm:hidden"
                        }, React.createElement(Link.default, {
                              href: "/",
                              children: React.createElement("a", {
                                    className: "w-24"
                                  }, React.createElement("img", {
                                        src: "/static/reason_logo.svg"
                                      }))
                            }), React.createElement("span", {
                              className: "inline-block text-center w-6 text-2xl font-bold",
                              onClick: (function (param) {
                                  return Curry._1(toggle, /* () */0);
                                })
                            }, Util.ReactStuff.s("X"))), React.createElement("div", {
                          className: "flex flex-col sm:flex-row sm:justify-between sm:w-3/4 max-w-sm"
                        }, React.createElement(Link.default, {
                              href: "/try",
                              children: React.createElement("a", {
                                    className: linkOrActiveLink("/try", route) + " font-bold"
                                  }, Util.ReactStuff.s("Playground"))
                            }), React.createElement(Link.default, {
                              href: "/blog",
                              children: React.createElement("a", {
                                    className: linkOrActiveLink("/blog", route) + " font-bold"
                                  }, Util.ReactStuff.s("Blog"))
                            }), React.createElement(Link.default, {
                              href: "/community",
                              children: React.createElement("a", {
                                    className: linkOrActiveLink("/community", route) + " font-bold"
                                  }, Util.ReactStuff.s("Community"))
                            }), React.createElement(Navigation$CollapsibleLink, {
                              title: "API",
                              route: route,
                              href: "/api",
                              children: Util.ReactStuff.s("Items")
                            }), React.createElement(Navigation$CollapsibleLink, {
                              title: "Docs",
                              route: route,
                              href: "/docs",
                              children: Util.ReactStuff.s("Items")
                            })), React.createElement("div", {
                          className: "flex"
                        }, React.createElement("a", {
                              className: link,
                              href: "https://github.com/reason-association/reasonml.org",
                              rel: "noopener noreferrer",
                              target: "_blank"
                            }, React.createElement(Icon.Github.make, {
                                  className: "w-6 h-6"
                                })), React.createElement("a", {
                              className: link,
                              href: "https://twitter.com/reasonml",
                              rel: "noopener noreferrer",
                              target: "_blank"
                            }, React.createElement(Icon.Twitter.make, {
                                  className: "w-6 h-6"
                                })), React.createElement("a", {
                              className: link,
                              href: "https://discord.gg/reasonml",
                              rel: "noopener noreferrer",
                              target: "_blank"
                            }, React.createElement(Icon.Discord.make, {
                                  className: "w-6 h-6"
                                }))), React.createElement("button", {
                          className: "sm:border-l sm:border-r sm:border-night sm:h-full"
                        }, React.createElement("img", {
                              className: "w-6 h-6",
                              src: "/static/ic_search_small.svg"
                            })))));
}

function Navigation$ApiDocs(Props) {
  var route = Props.route;
  var versionInfo = Props.versionInfo;
  return React.createElement("nav", {
              className: "fixed z-10 top-0 p-2 w-full h-16 bg-night-dark shadow flex items-center text-white-80 text-sm",
              id: "header"
            }, React.createElement(Link.default, {
                  href: "/",
                  children: React.createElement("a", {
                        className: "flex items-center w-40"
                      }, React.createElement("img", {
                            className: "h-10",
                            src: "/static/reason_logo.svg"
                          }))
                }), React.createElement("div", {
                  className: "ml-6 flex w-3/5 px-3 h-10 max-w-sm rounded-lg text-white bg-light-grey-20 content-center items-center w-2/3"
                }, React.createElement("img", {
                      "aria-hidden": true,
                      className: "mr-3",
                      src: "/static/ic_search_small.svg"
                    }), React.createElement("input", {
                      className: "bg-transparent placeholder-white-80 block focus:outline-none w-full ml-2",
                      placeholder: "Search not ready yet...",
                      type: "text"
                    })), React.createElement("div", {
                  className: "flex mx-4 text-white-80 justify-between ml-auto"
                }, React.createElement(Link.default, {
                      href: "/api",
                      children: React.createElement("a", {
                            className: linkOrActiveLink("/api", route)
                          }, Util.ReactStuff.s("API"))
                    }), React.createElement("a", {
                      className: "no-underline block text-inherit hover:text-white text-white-80 align-middle ml-6",
                      href: "https://github.com/reason-association/reasonml.org",
                      rel: "noopener noreferrer",
                      target: "_blank"
                    }, Util.ReactStuff.s("Github")), versionInfo !== undefined ? React.createElement("a", {
                        className: "bg-light-grey-20 leading-normal ml-6 px-1 rounded text-light-grey text-xs",
                        href: "https://github.com/BuckleScript/bucklescript/releases",
                        rel: "noopener noreferrer",
                        target: "_blank"
                      }, Util.ReactStuff.s(versionInfo)) : null));
}

var ApiDocs = {
  make: Navigation$ApiDocs
};

var Link$1 = 0;

var make = Navigation;

export {
  Link$1 as Link,
  link ,
  activeLink ,
  linkOrActiveLink ,
  CollapsibleLink ,
  make ,
  ApiDocs ,
  
}
/* Icon Not a pure module */
