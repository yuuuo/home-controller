import useSWRMutation from "swr/mutation";

export const useAirConditionerByTemperatureMutation = () => {
  return useSWRMutation(
    "/air-conditioner",
    async (_, { arg }: { arg: { temperature: number } }) => {
      await fetch(`${import.meta.env.VITE_IR_BASE_URL}/air-conditioner/`, {
        method: "POST",
        body: JSON.stringify({
          temperature: arg.temperature,
          status: true,
        }),
      });
    }
  );
};

export const useAirConditionerOffMutation = () => {
  return useSWRMutation("/air-conditioner", async () => {
    await fetch(`${import.meta.env.VITE_IR_BASE_URL}/air-conditioner/`, {
      method: "POST",
      body: JSON.stringify({
        status: false,
      }),
    });
  });
};
