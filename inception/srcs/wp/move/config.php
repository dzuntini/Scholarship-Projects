<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the installation.
 * You don't have to use the web site, you can copy this file to "wp-config.php"
 * and fill in the values.
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
define( 'DB_NAME', getenv( 'MARIADB_DATABASE' ) );

/** MySQL database username */
define( 'DB_USER', getenv( 'MARIADB_USER' ) );

/** MySQL database password */
define( 'DB_PASSWORD', getenv( 'MARIADB_PASSWORD' ) );

/** MySQL hostname */
define( 'DB_HOST', 'mariadb:3306' );

define( 'WP_SITEURL', 'https://dzuntini.42.fr');
define( 'WP_HOME', 'https://dzuntini.42.fr');

/** Database charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The database collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication unique keys and salts.
 *
 * Change these to different unique phrases! You can generate these using
 * the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}.
 *
 * You can change these at any point in time to invalidate all existing cookies.
 * This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         'v!EK.-[v?wulzX|CjIXZuYYuk?%)F&b9t*/5:%}P DSI|CmGP}F]))|o:mQhkxh*');
define('SECURE_AUTH_KEY',  'Wb<P&o&`+hsj398q1>.(Jz*<;V#:922aa~Uf2gyWV;4grHs|:?W;{n1R/D`F7VA<');
define('LOGGED_IN_KEY',    ';g.VgD1sG*|HKO8,}2$E@7$TGs98Wj0-<TXojqAO<>O4k6|Y,|@o[-cD#aLsfiO[');
define('NONCE_KEY',        'T-S:L,oYR=n26oH!{na:@<X-k, O+tHA!`{e}(#V}ohhQ;mK1Q@uFp-c4u)xopr ');
define('AUTH_SALT',        '^En]^4cI&(IrdA2B`~`G`yqJd+b#UWp VAX@+ET^M69:M9i{ytg+$K]Z@B-< U!,');
define('SECURE_AUTH_SALT', 'Z{V}Y?$und#[6HkWta}ODnsu2T;U*LmFI`d-^ oM&8S-l@b_+,Ia70Py3g!djD>v');
define('LOGGED_IN_SALT',   '+xJ=mF%Ksm;!P`#;GH1co|+E#`5{.OolI{IB5.qcM>sf&ht<qWy?&,K-MUp-i+0J');
define('NONCE_SALT',       '16w5wO1{lm8&C9y?Sku!^6mEuJ7=qmP<BR=|j%|_(sy%-?fF;p]1qnf/`i@yIQKv');

/**#@-*/

/**
 * WordPress database table prefix.
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

/* Add any custom values between this line and the "stop editing" line. */



/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
