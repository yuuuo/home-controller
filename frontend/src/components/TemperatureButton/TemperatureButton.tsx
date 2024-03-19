import { memo, useCallback } from "react";
import { Button } from "@mui/material";

export type Props = {
  temperature: number;
  onClick(temperature: number): void;
};

export const TemperatureButton = memo(
  ({ temperature, onClick }: Props): JSX.Element => {
    const handleClick = useCallback(() => {
      onClick(temperature);
    }, [onClick, temperature]);

    return (
      <Button variant="outlined" color="primary" onClick={handleClick}>
        {temperature}
      </Button>
    );
  }
);
