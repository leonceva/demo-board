import React from "react";
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

  const sensorClicked = async (name) => {
    props.setIsFetching(true)
    switch (name) {
      case "Gyroscope":
        props.setIsLoading([true, false, false]);
        try {
          var gyro_data = await getGyroData();
        } catch (e) {
          console.log("Data request Failed: %s", e);
          props.setSensorValue(null);
          alert(`Failed to retrieve data: \n` + e);
          props.setIsFetching(false)
          break;
        }
        if (gyro_data.data === "TIMEOUT" || gyro_data.data === "FAILED") {
          props.setSensorValue(null);
          alert(gyro_data.data);
          props.setIsFetching(false)
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
          props.setSensorValue(sensor_data);
          props.setIsFetching(false)
          break;
        }

      case "Potentiometer":
        props.setIsLoading([false, true, false]);
        try {
          var pot_data = await getPotData();
        } catch (e) {
          console.log("Data request Failed: %s", e);
          props.setSensorValue(null);
          alert(`Failed to retrieve data: \n` + e);
          props.setIsFetching(false)
          break;
        }
        if (pot_data.data === "TIMEOUT" || pot_data.data === "FAILED") {
          props.setSensorValue(null);
          alert(pot_data.data);
          props.setIsFetching(false)
          break;
        } else {
          console.log(pot_data.data);
          var sensor_value = (pot_data.data / 1023) * 3.3;
          console.log(sensor_value);
          props.setSensorValue(sensor_value.toFixed(2));
          props.setIsFetching(false)
          break;
        }

      case "Switch":
        props.setIsLoading([false, false, true]);
        try {
          var switch_status = await getSwitchData();
        } catch (e) {
          console.log("Data request Failed: %s", e);
          props.setSensorValue(null);
          alert(`Failed to retrieve data: \n` + e);
          props.setIsFetching(false)
          break;
        }
        if (
          switch_status.data === "TIMEOUT" ||
          switch_status.data === "FAILED"
        ) {
          props.setSensorValue(null);
          alert(switch_status.data);
          props.setIsFetching(false)
          break;
        } else {
          console.log(switch_status.data);
          props.setSensorValue(switch_status.data);
          console.log(typeof switch_status.data);
          props.setIsFetching(false)
          break;
        }

      default:
        break;
    }
    props.setIsLoading([false, false, false]);
  };

  return (
    <button
      disabled={props.disabled || props.isFetching}
      onClick={() => sensorClicked(props.name)}
      className='border border-2 border-dark rounded-pill pb-3 mt-2 mb-2 sensor-button'
      style={{ justifyContent: "center" }}
    >
      <div className='row fs-2'>
        <p>{displayName(props.name)}</p>
      </div>
      <div
        className='row d-inline-flex bg-white ps-3 pe-3 sensor-value'
        style={{ justifyContent: "center" }}
      >
        {!props.isLoading ? (
          <div className='m-1' >
            {props.sensorValue != null ?
              props.name === "Switch" ?
                props.sensorValue === "ON" ?
                  <div style={{ color: "green" }}>{props.sensorValue}</div> :
                  <div style={{ color: "red" }}>{props.sensorValue}</div>
                : <div>{props.sensorValue}</div>
              : <div>N/A</div>}
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
