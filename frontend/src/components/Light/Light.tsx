import { memo, useCallback, useState } from "react";
import { FormControlLabel, Switch, Typography } from "@mui/material";
import { useLightQuery } from "~/hooks/query/light";

export const Light = memo((): JSX.Element => {
  const [isOn, setIsOn] = useState<boolean>(true);
  const { trigger } = useLightQuery();

  const handleChange = useCallback(
    (event: React.ChangeEvent<HTMLInputElement>) => {
      const checked = event.target.checked;
      setIsOn(checked);
      trigger({ isOn: checked });
    },
    [trigger]
  );

  return (
    <>
      <Typography variant="h6" mb={1}>
        Light
      </Typography>
      <FormControlLabel
        value="light"
        control={
          <Switch color="primary" onChange={handleChange} checked={isOn} />
        }
        label="Light"
        labelPlacement="top"
      />
    </>
  );
});
