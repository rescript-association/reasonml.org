

import * as Icon from "./Icon.bs.js";
import * as Util from "../common/Util.bs.js";
import * as Caret from "./Caret.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Link from "next/link";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as ColorTheme from "../common/ColorTheme.bs.js";
import * as Caml_chrome_debugger from "bs-platform/lib/es6/caml_chrome_debugger.js";

var link = "no-underline block text-inherit hover:cursor-pointer hover:text-white text-white-80 mb-px";

var activeLink = "text-inherit font-normal text-fire-80 border-b border-fire-80";

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
  var onStateChange = Props.onStateChange;
  var match = Props.allowHover;
  var allowHover = match !== undefined ? match : true;
  var id = Props.id;
  var state = Props.state;
  var match$1 = Props.active;
  var active = match$1 !== undefined ? match$1 : false;
  var children = Props.children;
  var onMouseDown = function (evt) {
    evt.preventDefault();
    evt.stopPropagation();
    return Curry._2(onStateChange, id, state >= 2 ? /* KeepOpen */0 : /* Closed */2);
  };
  var onMouseEnter = function (evt) {
    evt.preventDefault();
    if (allowHover) {
      return Curry._2(onStateChange, id, /* HoverOpen */1);
    } else {
      return 0;
    }
  };
  var isOpen = state < 2;
  var direction = isOpen ? /* Up */19067 : /* Down */759637122;
  return React.createElement("div", {
              className: "sm:font-normal relative",
              onMouseEnter: onMouseEnter
            }, React.createElement("div", {
                  className: "flex items-center"
                }, React.createElement("a", {
                      className: (
                        active ? activeLink : link
                      ) + (" flex items-center hover:cursor-pointer " + (
                          isOpen ? " text-white" : ""
                        )),
                      onMouseDown: onMouseDown
                    }, Util.ReactStuff.s(title), React.createElement("span", {
                          className: "fill-current flex-no-wrap inline-block ml-2 w-3 h-2"
                        }, React.createElement(Caret.make, {
                              direction: direction
                            })))), React.createElement("div", {
                  className: (
                    isOpen ? "block" : "hidden"
                  ) + " sm:fixed sm:left-0 sm:border-night sm:mt-4 sm:border-t bg-night-dark w-full h-16"
                }, children));
}

var CollapsibleLink = {
  make: Navigation$CollapsibleLink
};

function useOutsideClick (outerRef,trigger){{
      function handleClickOutside(event) {
        if (outerRef.current && !outerRef.current.contains(event.target)) {
          trigger();
        }
      }

      React.useEffect(() => {
        document.addEventListener("mousedown", handleClickOutside);
        return () => {
          document.removeEventListener("mousedown", handleClickOutside);
        };
      });

    }};

function useWindowWidth (){{
  const isClient = typeof window === 'object';

  function getSize() {
    return {
      width: isClient ? window.innerWidth : undefined,
      height: isClient ? window.innerHeight : undefined
    };
  }

  const [windowSize, setWindowSize] = React.useState(getSize);

  React.useEffect(() => {
    if (!isClient) {
      return false;
    }

    function handleResize() {
      setWindowSize(getSize());
    }

    window.addEventListener('resize', handleResize);
    return () => window.removeEventListener('resize', handleResize);
  }, []); // Empty array ensures that effect is only run on mount and unmount

  if(windowSize) {
    return windowSize.width;
  }
  return null;
  }};

function Navigation$SubNav$DocsLinkSection(Props) {
  return React.createElement("div", undefined, Util.ReactStuff.s("Docs Items"));
}

var DocsLinkSection = {
  make: Navigation$SubNav$DocsLinkSection
};

function Navigation$SubNav$ApisLinkSection(Props) {
  var jsTheme = ColorTheme.toCN(/* Js */16617);
  var reTheme = ColorTheme.toCN(/* Reason */825328612);
  return React.createElement("div", {
              className: ""
            }, React.createElement("div", {
                  className: reTheme
                }, React.createElement(Link.default, {
                      href: "/apis",
                      children: React.createElement("a", {
                            className: "uppercase text-sm text-primary"
                          }, Util.ReactStuff.s("Overview"))
                    })), React.createElement("div", {
                  className: jsTheme
                }, React.createElement(Link.default, {
                      href: "/apis/javascript/latest",
                      children: React.createElement("a", {
                            className: "uppercase tracking-wide text-sm text-primary font-black"
                          }, Util.ReactStuff.s("JavaScript"))
                    })));
}

var ApisLinkSection = {
  make: Navigation$SubNav$ApisLinkSection
};

var SubNav = {
  DocsLinkSection: DocsLinkSection,
  ApisLinkSection: ApisLinkSection
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
  var match$3 = React.useState((function () {
          return /* array */[
                  /* record */Caml_chrome_debugger.record([
                      "title",
                      "children",
                      "href",
                      "state"
                    ], [
                      "Docs",
                      React.createElement(Navigation$SubNav$DocsLinkSection, { }),
                      "/docs",
                      2
                    ]),
                  /* record */Caml_chrome_debugger.record([
                      "title",
                      "children",
                      "href",
                      "state"
                    ], [
                      "API",
                      React.createElement(Navigation$SubNav$ApisLinkSection, { }),
                      "/apis",
                      2
                    ])
                ];
        }));
  var setCollapsibles = match$3[1];
  var resetCollapsibles = function (param) {
    return Curry._1(setCollapsibles, (function (prev) {
                  return Belt_Array.map(prev, (function (c) {
                                return /* record */Caml_chrome_debugger.record([
                                          "title",
                                          "children",
                                          "href",
                                          "state"
                                        ], [
                                          c[/* title */0],
                                          c[/* children */1],
                                          c[/* href */2],
                                          2
                                        ]);
                              }));
                }));
  };
  var outerRef = React.useRef(null);
  useOutsideClick(outerRef, resetCollapsibles);
  var windowWidth = Curry._1(useWindowWidth, /* () */0);
  var allowHover = windowWidth !== undefined ? windowWidth > 576 : true;
  return React.createElement("nav", {
              ref: outerRef,
              className: "fixed flex justify-center z-10 top-0 w-full h-16 bg-night-dark shadow text-white-80 text-xl sm:text-base",
              id: "header",
              style: {
                minWidth: minWidth
              }
            }, React.createElement("div", {
                  className: "flex justify-between pl-4 items-center h-full w-full sm:max-w-xl"
                }, React.createElement("div", {
                      className: "lg:mb-3 w-8 lg:w-20"
                    }, React.createElement(Link.default, {
                          href: "/",
                          children: React.createElement("a", undefined, React.createElement("picture", undefined, React.createElement("source", {
                                        media: "(min-width: 993px)",
                                        srcSet: "/static/reason_logo_full.svg"
                                      }), React.createElement("img", {
                                        className: "h-8 w-auto inline-block",
                                        src: "/static/reason_logo.svg"
                                      })))
                        })), React.createElement("button", {
                      className: "h-full px-4 sm:hidden flex items-center hover:text-white",
                      onClick: (function (evt) {
                          evt.preventDefault();
                          return Curry._1(toggle, /* () */0);
                        })
                    }, React.createElement("img", {
                          className: "w-full block",
                          src: "/static/ic_drawer_dots.svg"
                        })), React.createElement("div", {
                      className: (
                        isOpen ? "flex" : "hidden"
                      ) + " flex-col fixed top-0 left-0 h-full sm:w-9/12 bg-night-dark sm:h-auto sm:flex sm:relative sm:flex-row sm:justify-between",
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
                              onClick: (function (evt) {
                                  evt.preventDefault();
                                  return Curry._1(toggle, /* () */0);
                                })
                            }, Util.ReactStuff.s("X"))), React.createElement("div", {
                          className: "flex flex-col sm:flex-row sm:justify-between sm:w-full max-w-sm"
                        }, React.createElement(Link.default, {
                              href: "/try",
                              children: React.createElement("a", {
                                    className: linkOrActiveLink("/try", route)
                                  }, Util.ReactStuff.s("Playground"))
                            }), React.createElement(Link.default, {
                              href: "/blog",
                              children: React.createElement("a", {
                                    className: linkOrActiveLink("/blog", route)
                                  }, Util.ReactStuff.s("Blog"))
                            }), React.createElement(Link.default, {
                              href: "/community",
                              children: React.createElement("a", {
                                    className: linkOrActiveLink("/community", route)
                                  }, Util.ReactStuff.s("Community"))
                            }), Util.ReactStuff.ate(Belt_Array.mapWithIndex(match$3[0], (function (idx, c) {
                                    var title = c[/* title */0];
                                    var onStateChange = function (id, state) {
                                      return Curry._1(setCollapsibles, (function (prev) {
                                                    return Belt_Array.map(prev, (function (c) {
                                                                  if (c[/* title */0] === id) {
                                                                    return /* record */Caml_chrome_debugger.record([
                                                                              "title",
                                                                              "children",
                                                                              "href",
                                                                              "state"
                                                                            ], [
                                                                              c[/* title */0],
                                                                              c[/* children */1],
                                                                              c[/* href */2],
                                                                              state
                                                                            ]);
                                                                  } else {
                                                                    return /* record */Caml_chrome_debugger.record([
                                                                              "title",
                                                                              "children",
                                                                              "href",
                                                                              "state"
                                                                            ], [
                                                                              c[/* title */0],
                                                                              c[/* children */1],
                                                                              c[/* href */2],
                                                                              2
                                                                            ]);
                                                                  }
                                                                }));
                                                  }));
                                    };
                                    return React.createElement(Navigation$CollapsibleLink, {
                                                title: title,
                                                onStateChange: onStateChange,
                                                allowHover: allowHover,
                                                id: title,
                                                state: c[/* state */3],
                                                active: route.startsWith(c[/* href */2]),
                                                children: c[/* children */1],
                                                key: String(idx)
                                              });
                                  })))), React.createElement("div", {
                          className: "hidden lg:flex lg:justify-between lg:w-2/12"
                        }, React.createElement("a", {
                              className: link,
                              href: "https://github.com/reason-association/reasonml.org",
                              rel: "noopener noreferrer",
                              target: "_blank"
                            }, React.createElement(Icon.Github.make, {
                                  className: "w-5 h-5"
                                })), React.createElement("a", {
                              className: link,
                              href: "https://twitter.com/reasonml",
                              rel: "noopener noreferrer",
                              target: "_blank"
                            }, React.createElement(Icon.Twitter.make, {
                                  className: "w-5 h-5"
                                })), React.createElement("a", {
                              className: link,
                              href: "https://discord.gg/reasonml",
                              rel: "noopener noreferrer",
                              target: "_blank"
                            }, React.createElement(Icon.Discord.make, {
                                  className: "w-5 h-5"
                                })))), React.createElement("button", {
                      className: "hidden sm:flex sm:w-16 sm:justify-center sm:border-l sm:border-r sm:border-night sm:h-full"
                    }, React.createElement("img", {
                          className: "w-6 h-6",
                          src: "/static/ic_search_small.svg"
                        }))));
}

var Link$1 = 0;

var make = Navigation;

export {
  Link$1 as Link,
  link ,
  activeLink ,
  linkOrActiveLink ,
  CollapsibleLink ,
  useOutsideClick ,
  useWindowWidth ,
  SubNav ,
  make ,
  
}
/* Icon Not a pure module */
