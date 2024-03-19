import { memo, useCallback } from "react";
import { Typography } from "@mui/material";
import {
  CartesianGrid,
  Legend,
  Line,
  LineChart,
  Tooltip,
  XAxis,
  YAxis,
} from "recharts";
import { useEnvironmentQuery } from "~/hooks/query/environment";
import { format } from "date-fns";

export const Environment = memo((): JSX.Element => {
  const { data } = useEnvironmentQuery();

  console.log(data);

  const tickFormatter = useCallback((tick: string) => {
    return format(new Date(tick), "HH:mm:ss");
  }, []);

  return (
    <>
      <Typography variant="h6" mb={1}>
        Environment Graph
      </Typography>
      <LineChart
        width={800}
        height={400}
        data={data}
        margin={{
          top: 30,
          right: 30,
          left: 20,
          bottom: 20,
        }}
      >
        <CartesianGrid strokeDasharray="3 3" />
        <XAxis
          dataKey="datetime"
          tickFormatter={tickFormatter}
          label={{
            value: "日時",
            offset: -5,
            position: "insideBottomRight",
          }}
        />
        <YAxis
          yAxisId={1}
          label={{
            value: "気温(°C)",
            angle: -90,
          }}
        />
        <YAxis
          yAxisId={2}
          orientation="right"
          domain={[0, 100]}
          label={{
            value: "湿度(%)",
            angle: -90,
          }}
        />
        <Tooltip />
        <Legend verticalAlign="bottom" />
        <Line
          yAxisId={1}
          type="monotone"
          dataKey="temperature"
          name="気温"
          stroke="#8884d8"
          dot={false}
        />
        <Line
          yAxisId={2}
          type="monotone"
          dataKey="humidity"
          name="湿度"
          stroke="#8884d8"
          dot={false}
        />
      </LineChart>
    </>
  );
});
