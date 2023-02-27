import { registerAs } from '@nestjs/config';

export default registerAs('jwt', () => ({
  secret: process.env.NEST_JWT_SECRET,
  expiresIn: process.env.NEST_JWT_EXPIRES_IN,
}));
