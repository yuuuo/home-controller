import { Paper, Stack } from "@mui/material";
import { AirConditioner } from "../components/AirConditioner";
import { Environment } from "../components/Environment";
import { Light } from "../components/Light";

export const RemoteContoroller = (): JSX.Element => {
  return (
    <Stack gap={2}>
      <Paper sx={{ p: 2 }}>
        <AirConditioner />
      </Paper>
      <Paper sx={{ p: 2 }}>
        <Light />
      </Paper>
      <Paper sx={{ p: 2 }}>
        <Environment />
      </Paper>
    </Stack>
  );
};
