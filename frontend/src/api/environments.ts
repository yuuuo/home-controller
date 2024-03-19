import type { DefineMethods } from "aspida";

export type Environment = {
  humidity: number;
  datetime: string;
  temperature: number;
};

export type Methods = DefineMethods<{
  get: {
    resBody: Environment[];
  };
  post: {
    reqBody: Omit<Environment, "datetime">;
  };
}>;
