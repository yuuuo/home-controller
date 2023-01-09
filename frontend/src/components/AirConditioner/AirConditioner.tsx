import { memo, useCallback } from "react";
import { Button, Stack, Typography } from "@mui/material";
import {
  useAirConditionerByTemperatureMutation,
  useAirConditionerOffMutation,
} from "~/hooks/query/airConditioner";
import { TemperatureButton } from "../TemperatureButton";

export const AirConditioner = memo((): JSX.Element => {
  const { trigger: onTrigger } = useAirConditionerByTemperatureMutation();
  const { trigger: offTrigger } = useAirConditionerOffMutation();

  const handleTemperatureClick = useCallback(
    (temperature: number) => {
      onTrigger({ temperature });
    },
    [onTrigger]
  );

  const handleOffClick = useCallback(() => {
    offTrigger();
  }, [offTrigger]);

  return (
    <>
      <Typography variant="h6" mb={1}>
        AirConditioner
      </Typography>
      <Stack direction="row" gap={2}>
        {[20, 26, 27, 28].map((temp) => {
          return (
            <TemperatureButton
              key={temp}
              temperature={temp}
              onClick={handleTemperatureClick}
            />
          );
        })}
        <Button variant="outlined" color="primary" onClick={handleOffClick}>
          OFF
        </Button>
      </Stack>
    </>
  );
});
