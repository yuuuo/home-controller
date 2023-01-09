import useSWRMutation from "swr/mutation";

export const useLightQuery = () => {
  return useSWRMutation(
    "/light",
    async (_, { arg: { isOn } }: { arg: { isOn: boolean } }) => {
      // TODO
      console.log(isOn);
    }
  );
};
