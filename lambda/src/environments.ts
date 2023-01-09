import { Router } from "express";
import { z } from "zod";

import { tableName } from "../lib/lambda-stack";
import type { DynamoDBClientConfig } from "@aws-sdk/client-dynamodb";
import { DynamoDBClient } from "@aws-sdk/client-dynamodb";
import {
  DynamoDBDocumentClient,
  ScanCommand,
  PutCommand,
} from "@aws-sdk/lib-dynamodb";
import { formatISO } from "date-fns";

const router = Router();

router.get("/", async (_req, res) => {
  const config: DynamoDBClientConfig = {};
  const client = new DynamoDBClient(config);
  const dynamo = DynamoDBDocumentClient.from(client);
  const command = new ScanCommand({
    TableName: tableName,
  });

  const result = await dynamo.send(command);
  res.json(result.Items);
});

router.put("/", async (req, res) => {
  const schema = z.object({
    temperature: z.number(),
    humidity: z.number(),
  });

  const data = schema.parse(req.body);
  const config: DynamoDBClientConfig = {};
  const dynamo = new DynamoDBClient(config);
  const command = new PutCommand({
    TableName: tableName,
    Item: {
      datetime: formatISO(new Date()),
      temperature: data.temperature,
      humidity: data.humidity,
    },
  });

  await dynamo.send(command);
  res.status(204).send();
});

export { router as environments };
