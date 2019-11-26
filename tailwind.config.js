/*
 *
 * Color naming convention:
 *
 * Color with opacity:
 * --------
 * grey-80 => grey with 80% opacity
 *
 * Solid Color:
 * --------
 * grey => grey with RGB value
 *
 * Categorizing colors w/ modifiers:
 * --------
 *
 * night
 *  night-lighter -> even lighter version
 *  night-light -> lighter version (obviously)
 *  night -> base color
 *  night-dark -> darker version
 *  night-darker -> even darker version
 *
 *  -> If we run out of modifiers, we need to define a new
 *     color name!
 *
 * In case with opacity:
 * night-80
 *  night-80-lighter
 *  night-80-light
 *  night-80
 *  night-80-dark
 *  night-80-darker
 *
 *
 */
module.exports = {
  theme: {
    extend: {
      colors: {
        night: {
          dark: "#0A0D2F",
          default: "#3E4057",
          light: "#727489",
          "10": "rgba(62, 64, 87, 0.10)"
        },
        snow: {
          dark: "#EAEBED",
          default: "#F4F4F5"
        },
        white: {
          default: "#FFFFFF",
          "80": "rgba(255,255,255,0.8)"
        },
        fire: {
          default: "#DF4B37",
          "80": "rgba(223, 75, 55, 0.8)",
          "40": "rgba(223, 75, 55, 0.4)"
        },
        gold: {
          light: "#FFC833",
          default: "#E0AC00",
          dark: "#C19400",
          "15": "rgba(224, 172, 0, 0.15)",
          "5": "rgba(224, 172, 0, 0.05)"
        },
        sky: {
          default: "#376FDD"
        },
        berry: {
          default: "#AB5EA3",
          "40": "rgba(171, 94, 163, 0.40)",
          "15": "rgba(171, 94, 163, 0.15)",
          "5": "rgba(171, 94, 163, 0.05)"
        },
        primary: {
          dark: "var(--color-text-primary-dark)",
          default: "var(--color-text-primary)",
          light: "var(--color-text-primary-light)",
          "5": "var(--color-text-primary-5)",
        },
        "light-grey": "rgba(245, 245, 245, 0.5)",
        "light-grey-20": "rgba(245, 245, 245, 0.2)",
        "ghost-white": "#F8F7F9"
      }
    },
    screens: {
      sm: "576px",
      md: "768px",
      lg: "992px",
      xl: "1200px"
    },
    /* Most of the time we customize the font-sizes,
     so we added the Tailwind default values here for
     convenience */
    fontSize: {
      xs: ".75rem", // 12px
      sm: ".8125rem", // 13px
      base: "1rem", // 16px
      lg: "1.0625rem", // 17px
      xl: "1.3125rem", // 21px
      "2xl": "1.5rem", // 24px
      "3xl": "2rem", // 32px
      "4xl": "2.125rem", // 34px
      "5xl": "2.25rem", // 36px
      "6xl": "2.625rem", // 42px
      "7xl": "4.875rem" // 78px
    },
    fontWeight: {
      hairline: 100,
      thin: 200,
      light: 300,
      normal: 400,
      medium: 500,
      semibold: 600,
      bold: 700,
      extrabold: 800,
      black: 900
    },
    lineHeight: {
      none: 1,
      tight: 1.25,
      normal: 1.875,
      loose: 2,
      "1": 1.15,
      "2": 1.3,
      "3": 1.4,
      "4": 1.5,
      "5": 1.75
    },
    letterSpacing: {
      tight: "-0.03em",
      normal: "0",
      wide: "0.075em"
    },
    maxWidth: {
      xs: "20rem", //  320px
      sm: "30rem", //  480px
      md: "40rem", //  640px
      lg: "50rem", //  800px
      xl: "60rem", //  960px
      "2xl": "70rem", // 1120px
      "3xl": "80rem", // 1280px
      "4xl": "90rem", // 1440px
      "5xl": "100rem", // 1600px
      full: "100%"
    },
    /* We override the default font-families with our own default prefs  */
    fontFamily: {
      montserrat: [
        "Montserrat",
        "-apple-system",
        "BlinkMacSystemFont",
        "Helvetica Neue",
        "Arial",
        "sans-serif"
      ],
      overpass: [
        "Overpass",
        "-apple-system",
        "BlinkMacSystemFont",
        "Helvetica Neue",
        "Arial",
        "sans-serif"
      ],
      mono: [
        "Roboto Mono",
        "SFMono-Regular",
        "Segoe UI",
        "Courier",
        "monospace"
      ]
    }
  },
  variants: {
    color: ["hover"],
    cursor: ["hover"],
    width: ["responsive"],
    border: ["hover", "responsive"],
    padding: ["hover", "responsive"],
  },
  plugins: []
};
