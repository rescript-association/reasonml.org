const bsconfig = require("./bsconfig.json");
const withCSS = require("@zeit/next-css");
const withTM = require("next-transpile-modules");
const path = require('path');
const remarkSlug = require('remark-slug');

const withMdx = require("./plugins/next-mdx")({
  extension: /\.mdx?$/,
  options: {
    remarkPlugins: [remarkSlug]
  }
});

let rescriptBase = "https://rescript-lang.org"
let manualBase = `${rescriptBase}/docs/manual/v8.0.0`
let apiBase = `${rescriptBase}/docs/manual/v8.0.0/api`

let apiPages = {
  '/apis/javascript/latest': `${apiBase}`,
  '/apis/javascript/latest/belt': `${apiBase}/belt`,
  '/apis/javascript/latest/belt/array': `${apiBase}/belt/array`,
  '/apis/javascript/latest/belt/debug': `${apiBase}/belt/debug`,
  '/apis/javascript/latest/belt/float': `${apiBase}/belt/float`,
  '/apis/javascript/latest/belt/hash': `${apiBase}/belt/hash`,
  '/apis/javascript/latest/belt/hash-map': `${apiBase}/belt/hash-map`,
  '/apis/javascript/latest/belt/hash-map-int': `${apiBase}/belt/hash-map-int`,
  '/apis/javascript/latest/belt/hash-map-string': `${apiBase}/belt/hash-map-string`,
  '/apis/javascript/latest/belt/hash-set': `${apiBase}/belt/hash-set`,
  '/apis/javascript/latest/belt/hash-set-int': `${apiBase}/belt/hash-set-int`,
  '/apis/javascript/latest/belt/hash-set-string': `${apiBase}/belt/hash-set-string`,
  '/apis/javascript/latest/belt/id': `${apiBase}/belt/id`,
  '/apis/javascript/latest/belt/int': `${apiBase}/belt/int`,
  '/apis/javascript/latest/belt/list': `${apiBase}/belt/list`,
  '/apis/javascript/latest/belt/map': `${apiBase}/belt/map`,
  '/apis/javascript/latest/belt/map-dict': `${apiBase}/belt/map-dict`,
  '/apis/javascript/latest/belt/map-int': `${apiBase}/belt/map-int`,
  '/apis/javascript/latest/belt/map-string': `${apiBase}/belt/map-string`,
  '/apis/javascript/latest/belt/mutable-map': `${apiBase}/belt/mutable-map`,
  '/apis/javascript/latest/belt/mutable-map-int': `${apiBase}/belt/mutable-map-int`,
  '/apis/javascript/latest/belt/mutable-map-string': `${apiBase}/belt/mutable-map-string`,
  '/apis/javascript/latest/belt/mutable-queue': `${apiBase}/belt/mutable-queue`,
  '/apis/javascript/latest/belt/mutable-set': `${apiBase}/belt/mutable-set`,
  '/apis/javascript/latest/belt/mutable-set-int': `${apiBase}/belt/mutable-set-int`,
  '/apis/javascript/latest/belt/mutable-set-string': `${apiBase}/belt/mutable-set-string`,
  '/apis/javascript/latest/belt/mutable-stack': `${apiBase}/belt/mutable-stack`,
  '/apis/javascript/latest/belt/option': `${apiBase}/belt/option`,
  '/apis/javascript/latest/belt/range': `${apiBase}/belt/range`,
  '/apis/javascript/latest/belt/result': `${apiBase}/belt/result`,
  '/apis/javascript/latest/belt/set': `${apiBase}/belt/set`,
  '/apis/javascript/latest/belt/set-dict': `${apiBase}/belt/set-dict`,
  '/apis/javascript/latest/belt/set-int': `${apiBase}/belt/set-int`,
  '/apis/javascript/latest/belt/set-string': `${apiBase}/belt/set-string`,
  '/apis/javascript/latest/belt/sort-array': `${apiBase}/belt/sort-array`,
  '/apis/javascript/latest/belt/sort-array-int': `${apiBase}/belt/sort-array-int`,
  '/apis/javascript/latest/belt/sort-array-string': `${apiBase}/belt/sort-array-string`,
  '/apis/javascript/latest/js': `${apiBase}/js`,
  '/apis/javascript/latest/js/array': `${apiBase}/js/array`,
  '/apis/javascript/latest/js/array-2': `${apiBase}/js/array-2`,
  '/apis/javascript/latest/js/cast': `${apiBase}/js/cast`,
  '/apis/javascript/latest/js/console': `${apiBase}/js/console`,
  '/apis/javascript/latest/js/date': `${apiBase}/js/date`,
  '/apis/javascript/latest/js/dict': `${apiBase}/js/dict`,
  '/apis/javascript/latest/js/exn': `${apiBase}/js/exn`,
  '/apis/javascript/latest/js/float': `${apiBase}/js/float`,
  '/apis/javascript/latest/js/fn': `${apiBase}/js/fn`,
  '/apis/javascript/latest/js/global': `${apiBase}/js/global`,
  '/apis/javascript/latest/js/int': `${apiBase}/js/int`,
  '/apis/javascript/latest/js/int-64': `${apiBase}/js/int-64`,
  '/apis/javascript/latest/js/json': `${apiBase}/js/json`,
  '/apis/javascript/latest/js/list': `${apiBase}/js/list`,
  '/apis/javascript/latest/js/math': `${apiBase}/js/math`,
  '/apis/javascript/latest/js/null': `${apiBase}/js/null`,
  '/apis/javascript/latest/js/null-undefined': `${apiBase}/js/null-undefined`,
  '/apis/javascript/latest/js/nullable': `${apiBase}/js/nullable`,
  '/apis/javascript/latest/js/obj': `${apiBase}/js/obj`,
  '/apis/javascript/latest/js/option': `${apiBase}/js/option`,
  '/apis/javascript/latest/js/primitive': `${apiBase}/js/primitive`,
  '/apis/javascript/latest/js/promise': `${apiBase}/js/promise`,
  '/apis/javascript/latest/js/re': `${apiBase}/js/re`,
  '/apis/javascript/latest/js/result': `${apiBase}/js/result`,
  '/apis/javascript/latest/js/string': `${apiBase}/js/string-2`,
  '/apis/javascript/latest/js/string-2': `${apiBase}/js/string-2`,

  '/apis/javascript/latest/js/typed-array': `${apiBase}/js/typed-array-2`,
  '/apis/javascript/latest/js/typed-array_array-buffer': `${apiBase}/js/typed-array-2_array-buffer`,
  '/apis/javascript/latest/js/typed-array_data-view': `${apiBase}/js/typed-array-2_data-view`,
  '/apis/javascript/latest/js/typed-array_float-32-array': `${apiBase}/js/typed-array-2_float-32-array`,
  '/apis/javascript/latest/js/typed-array_float-64-array': `${apiBase}/js/typed-array-2_float-64-array`,
  '/apis/javascript/latest/js/typed-array_int-16-array': `${apiBase}/js/typed-array-2_int-16-array`,
  '/apis/javascript/latest/js/typed-array_int-32-array': `${apiBase}/js/typed-array-2_int-32-array`,
  '/apis/javascript/latest/js/typed-array_int-8-array': `${apiBase}/js/typed-array-2_int-8-array`,
  '/apis/javascript/latest/js/typed-array_uint-16-array': `${apiBase}/js/typed-array_2-uint-16-array`,
  '/apis/javascript/latest/js/typed-array_uint-32-array': `${apiBase}/js/typed-array_2-uint-32-array`,
  '/apis/javascript/latest/js/typed-array_uint-8-array': `${apiBase}/js/typed-array-2_uint-8-array`,
  '/apis/javascript/latest/js/typed-array_uint-8-clamped-array': `${apiBase}/js/typed-array-2_uint-8-clamped-array`,

  '/apis/javascript/latest/js/typed-array-2': `${apiBase}/js/typed-array-2`,
  '/apis/javascript/latest/js/typed-array-2_array-buffer': `${apiBase}/js/typed-array-2_array-buffer`,
  '/apis/javascript/latest/js/typed-array-2_data-view': `${apiBase}/js/typed-array-2_data-view`,
  '/apis/javascript/latest/js/typed-array-2_float-32-array': `${apiBase}/js/typed-array-2_float-32-array`,
  '/apis/javascript/latest/js/typed-array-2_float-64-array': `${apiBase}/js/typed-array-2_float-64-array`,
  '/apis/javascript/latest/js/typed-array-2_int-16-array': `${apiBase}/js/typed-array-2_int-16-array`,
  '/apis/javascript/latest/js/typed-array-2_int-32-array': `${apiBase}/js/typed-array-2_int-32-array`,
  '/apis/javascript/latest/js/typed-array-2_int-8-array': `${apiBase}/js/typed-array-2_int-8-array`,
  '/apis/javascript/latest/js/typed-array-2_uint-16-array': `${apiBase}/js/typed-array_2-uint-16-array`,
  '/apis/javascript/latest/js/typed-array-2_uint-32-array': `${apiBase}/js/typed-array_2-uint-32-array`,
  '/apis/javascript/latest/js/typed-array-2_uint-8-array': `${apiBase}/js/typed-array-2_uint-8-array`,
  '/apis/javascript/latest/js/typed-array-2_uint-8-clamped-array': `${apiBase}/js/typed-array-2_uint-8-clamped-array`,

  '/apis/javascript/latest/js/types': `${apiBase}/js/types`,
  '/apis/javascript/latest/js/undefined': `${apiBase}/js/undefined`,
  '/apis/javascript/latest/js/unsafe': `${apiBase}/js/unsafe`,
  '/apis/javascript/latest/js/vector': `${apiBase}/js/vector`,
};

let bucklescriptPages = {
  '/docs/reason-compiler/latest/automatic-interface-generation': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/better-data-structures-printing-debug-mode': `${manualBase}/shared-data-types`,
  '/docs/reason-compiler/latest/bind-to-global-values': `${manualBase}/bind-to-global-values`,
  '/docs/reason-compiler/latest/browser-support-polyfills': `${manualBase}/browser-support-polyfills`,
  '/docs/reason-compiler/latest/build-advanced': `${manualBase}/build-advanced`,
  '/docs/reason-compiler/latest/build-configuration': `${manualBase}/build-configuration`,
  '/docs/reason-compiler/latest/build-overview': `${manualBase}/build-overview`,
  '/docs/reason-compiler/latest/build-performance': `${manualBase}/build-performance`,
  '/docs/reason-compiler/latest/class': `${manualBase}/bind-to-js-object#bind-to-a-js-object-thats-a-class`,
  '/docs/reason-compiler/latest/common-data-types': `${manualBase}/shared-data-types`,
  '/docs/reason-compiler/latest/comparison-to-jsoo': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/compiler-architecture-principles': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/concepts-overview': `${manualBase}/concepts-overview`,
  '/docs/reason-compiler/latest/conditional-compilation': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/decorators': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/difference-from-native-ocaml': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/embed-raw-javascript': `${manualBase}/embed-raw-javascript`,
  '/docs/reason-compiler/latest/exceptions': `${manualBase}/exception`,
  '/docs/reason-compiler/latest/extended-compiler-options': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/function': `${manualBase}/function`,
  '/docs/reason-compiler/latest/generate-converters-accessors': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/handling-js-naming-collisions': `${manualBase}/use-illegal-identifier-names`,
  '/docs/reason-compiler/latest/import-export': `${manualBase}/import-from-export-to-js`,
  '/docs/reason-compiler/latest/installation': `${manualBase}/installation`,
  '/docs/reason-compiler/latest/interop-cheatsheet': `${manualBase}/interop-cheatsheet`,
  '/docs/reason-compiler/latest/interop-misc': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/interop-overview': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/interop-with-js-build-systems': `${manualBase}/interop-with-js-build-systems`,
  '/docs/reason-compiler/latest/intro-to-external': `${manualBase}/external`,
  '/docs/reason-compiler/latest/introduction': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/json': `${manualBase}/json`,
  '/docs/reason-compiler/latest/new-project': `${manualBase}/installation#new-project`,
  '/docs/reason-compiler/latest/nodejs-special-variables': `${manualBase}/bind-to-global-js-values#special-global-values`,
  '/docs/reason-compiler/latest/null-undefined-option': `${manualBase}/null-undefined-option`,
  '/docs/reason-compiler/latest/object': `${manualBase}/bind-to-js-object`,
  '/docs/reason-compiler/latest/object-2': `${manualBase}/bind-to-js-object`,
  '/docs/reason-compiler/latest/pipe-first': `${manualBase}/pipe`,
  '/docs/reason-compiler/latest/property-access': `${manualBase}/bind-to-js-object#bind-using-special-bs-getters--setters`,
  '/docs/reason-compiler/latest/regular-expression': `${manualBase}/primitive-types#regular-expression`,
  '/docs/reason-compiler/latest/return-value-wrapping': `${manualBase}/bind-to-js-function#function-nullable-return-value-wrapping`,
  '/docs/reason-compiler/latest/stdlib-overview': `${manualBase}/`,
  '/docs/reason-compiler/latest/try': `${manualBase}/try`,
  '/docs/reason-compiler/latest/upgrade-to-v7': `${manualBase}/introduction`,
  '/docs/reason-compiler/latest/use-existing-ocaml-libraries': `${manualBase}/introduction`,
};

let manualPages = {
  '/docs/manual/latest/boolean': `${manualBase}/primitive-types#boolean`,
  '/docs/manual/latest/converting-from-js': `${manualBase}/converting-from-js`,
  '/docs/manual/latest/destructuring': `${manualBase}/pattern-matching-destructuring#destructuring`,
  '/docs/manual/latest/editor-plugins': `${manualBase}/editor-plugins`,
  '/docs/manual/latest/exception': `${manualBase}/exception`,
  '/docs/manual/latest/external': `${manualBase}/external`,
  '/docs/manual/latest/extra-goodies': `${manualBase}/introduction`,
  '/docs/manual/latest/faq': `${manualBase}/faq`,
  '/docs/manual/latest/function': `${manualBase}/function`,
  '/docs/manual/latest/if-else': `${manualBase}/control-flow#if-else--ternary`,
  '/docs/manual/latest/imperative-loops': `${manualBase}/control-flow#for-loops`,
  '/docs/manual/latest/installation': `${manualBase}/installation`,
  '/docs/manual/latest/integer-and-float': `${manualBase}/primitive-types`,
  '/docs/manual/latest/interop': `${manualBase}/embed-raw-javascript`,
  '/docs/manual/latest/introduction': `${manualBase}/introduction`,
  '/docs/manual/latest/jsx': `${manualBase}/jsx`,
  '/docs/manual/latest/lazy-values': `${manualBase}/lazy-values`,
  '/docs/manual/latest/let-binding': `${manualBase}/let-binding`,
  '/docs/manual/latest/libraries': `${manualBase}/libraries`,
  '/docs/manual/latest/list-and-array': `${manualBase}/array-and-list`,
  '/docs/manual/latest/module': `${manualBase}/module`,
  '/docs/manual/latest/more-on-type': `${manualBase}/type`,
  '/docs/manual/latest/mutation': `${manualBase}/mutation`,
  '/docs/manual/latest/native': `${manualBase}/introduction`,
  '/docs/manual/latest/native-quickstart': `${manualBase}/introduction`,
  '/docs/manual/latest/newcomer-examples': `${manualBase}/newcomer-examples`,
  '/docs/manual/latest/null-undefined-option': `${manualBase}/null-undefined-option`,
  '/docs/manual/latest/object': `${manualBase}/object`,
  '/docs/manual/latest/overview': `${manualBase}/overview`,
  '/docs/manual/latest/pattern-matching': `${manualBase}/pattern-matching-destructuring`,
  '/docs/manual/latest/pipe-first': `${manualBase}/pipe`,
  '/docs/manual/latest/pipe-last': `${manualBase}/pipe`,
  '/docs/manual/latest/project-structure': `${manualBase}/project-structure`,
  '/docs/manual/latest/promise': `${manualBase}/promise`,
  '/docs/manual/latest/quickstart-javascript': `${manualBase}/installation`,
  '/docs/manual/latest/record': `${manualBase}/record`,
  '/docs/manual/latest/reserved-keywords': `${manualBase}/reserved-keywords`,
  '/docs/manual/latest/string-and-char': `${manualBase}/primitive-types#string`,
  '/docs/manual/latest/syntax-cheatsheet': `${manualBase}/overview`,
  '/docs/manual/latest/tuple': `${manualBase}/tuple`,
  '/docs/manual/latest/type': `${manualBase}/type`,
  '/docs/manual/latest/variant': `${manualBase}/variant`,
};


let apiRedirects = Object.keys(apiPages).reduce((acc,key) => {
  acc.push({ source: key, destination: apiPages[key], permanent: true});
  return acc;
}, []);

let bucklescriptRedirects = Object.keys(bucklescriptPages).reduce((acc,key) => {
  acc.push({ source: key, destination: bucklescriptPages[key], permanent: true});
  return acc;
}, []);

let manualRedirects = Object.keys(manualPages).reduce((acc,key) => {
  acc.push({ source: key, destination: manualPages[key], permanent: true});
  return acc;
}, []);


console.log([...bucklescriptRedirects, manualRedirects]);

const config = {
  target: "serverless",
  pageExtensions: ["jsx", "js", "bs.js", "mdx"],
  transpileModules: ["bs-platform"].concat(bsconfig["bs-dependencies"]),
  async redirects() {
    return [
      ...apiRedirects,
      ...bucklescriptRedirects,
      ...manualRedirects,
      {
        source: '/blog',
        destination: 'https://rescript-lang.org/blog',
        permanent: true,
      },
      {
        source: '/blog/:slug*',
        destination: 'https://rescript-lang.org/blog/:slug*',
        permanent: true,
      },
    ]
  },
  env: {
    ENV: process.env.NODE_ENV,
  },
  webpack: (config, options) => {
    const { isServer } = options;
    if (!isServer) {
      // We shim fs for things like the blog slugs component
      // where we need fs access in the server-side part
      config.node = {
        fs: 'empty'
      }
    }
    return config
  }
};

module.exports = withMdx(withTM(withCSS(config)));
