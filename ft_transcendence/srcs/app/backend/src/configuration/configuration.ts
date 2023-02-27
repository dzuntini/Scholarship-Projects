export default () => ({
  port: parseInt(process.env.NEST_PORT) || 3000,
  host: process.env.HOST,
  frontUri: process.env.URI,
  salt: parseInt(process.env.SALT_ROUNDS) || 10,
});
