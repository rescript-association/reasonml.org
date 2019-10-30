open Util.ReactStuff;

[@react.component]
let make = (~code, ~lang) => {
  let highlighted = HighlightJs.(highlight(~lang, ~value=code)->valueGet);

  ReactDOMRe.createElementVariadic(
    "code",
    ~props=
      ReactDOMRe.objToDOMProps({
        "className": "text-xl text-night-dark hljs sig lang-" ++ lang,
        "dangerouslySetInnerHTML": {
          "__html": highlighted,
        },
      }),
    [||],
  );
};
