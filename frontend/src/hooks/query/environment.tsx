import type { SWRConfiguration } from "swr";
import useSWR from "swr";
import type { Environment } from "~/api/environments";
import { client } from "~/libs/client";

export const useEnvironmentQuery = (options?: SWRConfiguration) => {
  return useSWR(
    "/environment",
    async (): Promise<Environment[]> => {
      return await client.environments.$get();
    },
    options
  );
};
