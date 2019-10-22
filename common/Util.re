module ReactStuff = {
  let s = ReasonReact.string;
[@dead "ReactStuff.ate"]   let ate = ReasonReact.array;

  module Unsafe = {
    external elementAsString: React.element => string = "%identity";
  };
  module Style = ReactDOMRe.Style;
};