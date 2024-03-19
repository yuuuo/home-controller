import aspida from "@aspida/fetch";
import api from "../api/$api";

console.log(import.meta.env.VITE_SERVER_BASE_URL);
export const client = api(
  aspida(fetch, { baseURL: import.meta.env.VITE_SERVER_BASE_URL, mode: "cors" })
);
