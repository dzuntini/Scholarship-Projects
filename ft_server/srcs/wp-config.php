<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'valhalla' );

/** MySQL database username */
define( 'DB_USER', 'thor' );

/** MySQL database password */
define( 'DB_PASSWORD', 'thor' );

/** MySQL hostname */
define( 'DB_HOST', 'localhost' );

/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */

define('AUTH_KEY',         '*!FW@{+nj+_+0SyHGI_Dt,g2xb&H$n0rlC#GQQmt8&bAdyLUod0|vgPv;YJ6gZ!,');
define('SECURE_AUTH_KEY',  '9T]_u3HBI-|S7m+J8?~qQPbGr]CR~.rasFR8X6a+UhJal/jEY|PVvAK|y4ePh_`N');
define('LOGGED_IN_KEY',    '_[f]K6;=WdppD}dA%G{]2qk]G0[do&@k?R<F-%OH64XsaDt11p-*,ta> }wxnY%3');
define('NONCE_KEY',        'w5Gc(#d& !aNIsNLk:S_#sS/pm7^7>#g_~tlmI:/+AC|v`J-jYp8kPHS/+TU6d>x');
define('AUTH_SALT',        'u,Ys-jo7]gjmM%oAunS=S5Z+:>;b|DRe0lBTT EFe0F-s l:w3+gFr8lAe;f3>1H');
define('SECURE_AUTH_SALT', '^,y+cSk`cgrmeOGWmZ7o3I>KE{2_3H oD+P|hkB_Kd1Vz/_W+z$<M]VFCcq@zuu/');
define('LOGGED_IN_SALT',   '*-b<z6YAb<Q#{+woTyN;(tMbbF/V:kBGd_w7%%.8[+|+JXxG]V$S%;9@eakCWw@O');
define('NONCE_SALT',       '.B.9.Z;v)Y@1Uh.&n#,ij?j1+fez+pP($`32*Na~maVwO,~3w$Jj`JF9Q5siUZn*');

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

//define( 'FORCE_SSL_ADMIN', true);

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';