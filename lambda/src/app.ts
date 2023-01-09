import express, { Router } from "express";
import { environments } from "./environments";

const app = express();

const root = Router();

app.use(express.json());

root.get("/", (_req, res) => {
  res.json({ message: "Hello World!" });
});

app.use("/", root);

app.use("/environments", environments);

export { app };
