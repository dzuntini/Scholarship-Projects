import { registerAs } from '@nestjs/config';

export default registerAs('2fa', () => ({
  name: 'ft_trancsendance',
}));
