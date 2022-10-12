import React, { useState } from "react";
import { getGyroData, getPotData, getSwitchData } from "./api/sensorClient.js";

const displayName = (name) => {
  switch (name) {
    case "Gyroscope":
      return "Gyroscope Sensor";

    case "Potentiometer":
      return "Voltage Sensor";

    case "Switch":
      return "Switch Status";

    default:
      alert("Invalid Sensor Name: " + name);
      break;
  }
};

const SensorUnit = (props) => {
  const [sensorValue, setSensorValue] = useState(props.value);
  const [isLoading, setIsLoading] = useState(false);

  const sensorClicked = async (name) => {
    setIsLoading(true);
    switch (name) {
      case "Gyroscope":
        try {
          var gyro_data = await getGyroData();
        } catch (e) {
          console.log("Data request Failed: %s", e);
          setSensorValue(null);
          alert(`Failed to retrieve data: \n` + e);
          break;
        }
        if (gyro_data.data === "TIMEOUT" || gyro_data.data === "FAILED") {
          setSensorValue(null);
          alert(gyro_data.data);
          break;
        } else {
          var sensor_data = gyro_data.data.split(",");
          console.log(sensor_data);
          var value_1 = parseFloat(sensor_data[0]);
          var value_2 = parseFloat(sensor_data[1]);
          var value_3 = parseFloat(sensor_data[2]);
          sensor_data =
            String(value_1) + `, ` + String(value_2) + `, ` + String(value_3);
          console.log(sensor_data);
          setSensorValue(sensor_data);
          break;
        }

      case "Potentiometer":
        try {
          var pot_data = await getPotData();
        } catch (e) {
          console.log("Data request Failed: %s", e);
          setSensorValue(null);
          alert(`Failed to retrieve data: \n` + e);
          break;
        }
        if (pot_data.data === "TIMEOUT" || pot_data.data === "FAILED") {
          setSensorValue(null);
          alert(pot_data.data);
          break;
        } else {
          console.log(pot_data.data);
          var sensor_value = (pot_data.data / 1023) * 3.3;
          console.log(sensor_value);
          setSensorValue(sensor_value.toFixed(2));
          break;
        }

      case "Switch":
        try {
          var switch_status = await getSwitchData();
        } catch (e) {
          console.log("Data request Failed: %s", e);
          setSensorValue(null);
          alert(`Failed to retrieve data: \n` + e);
          break;
        }
        if (
          switch_status.data === "TIMEOUT" ||
          switch_status.data === "FAILED"
        ) {
          setSensorValue(null);
          alert(switch_status.data);
          break;
        } else {
          console.log(switch_status.data);
          setSensorValue(switch_status.data);
          console.log(typeof switch_status.data);
          break;
        }

      default:
        break;
    }
    setIsLoading(false);
  };

  return (
    <button
      disabled={props.disabled}
      onClick={() => sensorClicked(props.name)}
      className='border border-2 border-dark rounded-pill pb-3 mt-2 mb-2'
      style={{ justifyContent: "center" }}
    >
      <div className='row'>
        <p>{displayName(props.name)}</p>
      </div>
      <div
        className='row d-inline-flex bg-white ps-3 pe-3 sensor-value'
        style={{ justifyContent: "center" }}
      >
        {!isLoading ? (
          <div className='m-1'>
            {sensorValue != null ? <div>{sensorValue}</div> : <div>N/A</div>}
          </div>
        ) : (
          <div className='m-1'>
            <div
              className='spinner-grow spinner-grow-sm m-1 text-primary'
              role='status'
            />
            <div
              className='spinner-grow spinner-grow-sm m-1 text-primary'
              role='status'
            />
            <div
              className='spinner-grow spinner-grow-sm m-1 text-primary'
              role='status'
            />
          </div>
        )}
      </div>
    </button>
  );
};

export default SensorUnit;
