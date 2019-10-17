module Options = {
  [@bs.deriving abstract]
  type t = {
    [@bs.optional]
    id: string,
    [@bs.optional]
    shouldSort: bool,
    [@bs.optional]
    includeMatches: bool,
    [@bs.optional]
    matchAllTokens: bool,
    [@bs.optional]
    includeScore: bool,
    [@bs.optional]
    threshold: float,
    [@bs.optional]
    location: int,
    [@bs.optional]
    distance: int,
    [@bs.optional]
    maxPatternLength: int,
    [@bs.optional]
    minMatchCharLength: int,
    [@bs.optional]
    keys: array(string),
  };
};

type t('a);

type result = {
  .
  "item": string,
  "score": float,
};

[@bs.new] [@bs.module]
external make: (array('a), Options.t) => t('a) = "fuse.js";

[@bs.send] external search: (t('a), string) => array(result) = "search";
