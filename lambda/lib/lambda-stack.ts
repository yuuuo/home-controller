import type { StackProps, App } from "aws-cdk-lib";
import { Duration, Stack, RemovalPolicy, aws_apigateway } from "aws-cdk-lib";
import { RestApi, LambdaIntegration } from "aws-cdk-lib/aws-apigateway";
import { AttributeType, BillingMode, Table } from "aws-cdk-lib/aws-dynamodb";
import { Runtime } from "aws-cdk-lib/aws-lambda";
import { NodejsFunction, OutputFormat } from "aws-cdk-lib/aws-lambda-nodejs";
import path from "path";

export const tableName = "environment";

export class LambdaStack extends Stack {
  constructor(scope: App, id: string, props?: StackProps) {
    super(scope, id, props);

    const table = new Table(this, "home-controller-table", {
      tableName,
      partitionKey: {
        name: "datetime",
        type: AttributeType.STRING,
      },
      billingMode: BillingMode.PROVISIONED,
      readCapacity: 5,
      writeCapacity: 5,
      removalPolicy: RemovalPolicy.DESTROY,
    });

    const lambda = new NodejsFunction(this, "home-controller-lambda", {
      functionName: "home-controller-lambda",
      entry: path.join(__dirname, "../src/lambda.ts"),
      handler: "handler",
      runtime: Runtime.NODEJS_20_X,
      bundling: {
        format: OutputFormat.ESM,
        nodeModules: ["express", "@codegenie/serverless-express"],
      },
      memorySize: 512,
      timeout: Duration.seconds(10),
    });

    const api = new RestApi(this, "home-controller-api", {
      restApiName: "home-controller-api",
      defaultCorsPreflightOptions: {
        allowOrigins: aws_apigateway.Cors.ALL_ORIGINS,
      },
    });

    table.grantFullAccess(lambda);

    const trigger = new LambdaIntegration(lambda);

    api.root.addProxy({ anyMethod: true, defaultIntegration: trigger });
  }
}
