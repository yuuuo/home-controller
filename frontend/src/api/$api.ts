import type { AspidaClient } from 'aspida';
import type { Methods as Methods_8kpy1o } from './environments';

const api = <T>({ baseURL, fetch }: AspidaClient<T>) => {
  const prefix = (baseURL === undefined ? '' : baseURL).replace(/\/$/, '');
  const PATH0 = '/environments';
  const GET = 'GET';
  const POST = 'POST';

  return {
    environments: {
      $get: (option?: { config?: T | undefined } | undefined) =>
        fetch<Methods_8kpy1o['get']['resBody']>(prefix, PATH0, GET, option).json().then(r => r.body),
      $post: (option: { body: Methods_8kpy1o['post']['reqBody'], config?: T | undefined }) =>
        fetch(prefix, PATH0, POST, option).send().then(r => r.body),
      $path: () => `${prefix}${PATH0}`,
    },
  };
};

export type ApiInstance = ReturnType<typeof api>;
export default api;
