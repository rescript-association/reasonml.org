const bsconfig = require("./bsconfig.json");
const withCSS = require("@zeit/next-css");
const withTM = require("next-transpile-modules");

const withMdx = require("@next/mdx")({
  extension: /\.mdx?$/
});

const config = {
  target: "serverless",
  pageExtensions: ["jsx", "js", "bs.js", "mdx"],
  transpileModules: ["bs-platform"].concat(bsconfig["bs-dependencies"]),
  /*
  Required by reason package: https://www.npmjs.com/package/reason#javascript-api
  
  NOTE: refmt.js requires the node module fs, which of course isn't available on the web.
  If using webpack, to avoid the missing module error, put node: { fs: 'empty' } into webpack.config.js.
  See https://webpack.js.org/configuration/node/#other-node-core-libraries for more information.
  */
  webpack: (config, { isServer }) => {
    if (!isServer) {
      config.node = {
        fs: "empty"
      };
    }

    return config;
  }
};

module.exports = withMdx(withTM(withCSS(config)));
