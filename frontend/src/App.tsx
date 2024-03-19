import {
  AppBar,
  Box,
  createTheme,
  CssBaseline,
  ThemeProvider,
  Typography,
} from "@mui/material";
import { RemoteContoroller } from "./pages/RemoteController";

const App = (): JSX.Element => {
  const theme = createTheme({
    palette: {
      mode: "dark",
    },
  });
  return (
    <ThemeProvider theme={theme}>
      <CssBaseline />
      <AppBar position="static">
        <Box m={2} ml={4}>
          <Typography variant="h6">RemoteContoroller</Typography>
        </Box>
      </AppBar>
      <Box m={2}>
        <RemoteContoroller />
      </Box>
    </ThemeProvider>
  );
};

export default App;
