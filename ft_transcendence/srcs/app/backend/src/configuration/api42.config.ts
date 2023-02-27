import { registerAs } from '@nestjs/config';

export default registerAs('api42', () => ({
  uid: process.env.API42_UID,
  sec: process.env.API42_SEC,
  retaddr: process.env.API42_RETURN_ADDRES,
  authorizationURL: process.env.API42_AUTHORIZATION_URL,
  callbackURL: process.env.API42_CALLBACK_URL,
  tokenURL: process.env.API42_TOKEN_URL,
}));
