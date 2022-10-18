import React, { useEffect, useState } from "react";
import SensorUnit from "./sensorUnit";
import { getAllData } from "./api/sensorClient";

const SensorDashboard = (props) => {

    const [gyroValue, setGyroValue] = useState(null)
    const [potValue, setPotValue] = useState(null)
    const [switchValue, setSwitchValue] = useState(null)
    const [isLoading, setIsLoading] = useState([false, false, false]) // Gyro, Pot, Switch
    const [isFetching, setIsFetching] = useState(false)

    useEffect(() => {
        if (props.pingSensors === true) {
            console.log("Fetching all sensor data..")
            setIsLoading([true, true, true])
            if (props.pingSensors === true) {
                getAllData().then((res) => {
                    if (res.data === "TIMEOUT" || res.data === "FAILED") {
                        setGyroValue(null);
                        setPotValue(null)
                        setSwitchValue(null)
                        setIsLoading([false, false, false])
                        alert(res.data)
                    }
                    else {
                        console.log("Success")
                        var sensor_data = res.data.split(",")
                        // Gyro
                        const value_1 = parseFloat(sensor_data[0]);
                        const value_2 = parseFloat(sensor_data[1]);
                        const value_3 = parseFloat(sensor_data[2]);
                        const gyro_data =
                            String(value_1) + `, ` + String(value_2) + `, ` + String(value_3);
                        console.log(`Gyroscope: ${gyro_data}`);
                        setGyroValue(gyro_data)
                        // Pot
                        const pot_data = (sensor_data[3] / 1023) * 3.3;
                        console.log(`Potentiometer: ${pot_data}`)
                        setPotValue(pot_data.toFixed(2));
                        // Switch
                        const switch_data = sensor_data[4]
                        console.log(`Switch: ${switch_data}`)
                        setSwitchValue(switch_data)

                        setIsLoading([false, false, false])
                    }
                    props.setIsRunning(true)
                }).catch(e => {
                    console.log("Data request Failed: %s", e);
                    setGyroValue(null);
                    setPotValue(null)
                    setSwitchValue(null)
                    alert(`Failed to retrieve data: \n` + e);
                    props.setIsRunning(true)
                })
            }
        }
        props.setPingSensors(false)
        // eslint-disable-next-line
    }, [props.pingSensors])

    return (
        <div className="d-flex">
            <div className="dashboard col p-1 position-relative">
                <div className="row m-1 ps-2 pe-2">
                    <SensorUnit name="Gyroscope" disabled={props.automaticMode} isLoading={isLoading[0]}
                        setIsLoading={setIsLoading} sensorValue={gyroValue} setSensorValue={setGyroValue}
                        isFetching={isFetching} setIsFetching={setIsFetching} />
                </div>
                <div className="row m-1 ps-2 pe-2">
                    <SensorUnit name="Potentiometer" disabled={props.automaticMode} isLoading={isLoading[1]}
                        setIsLoading={setIsLoading} sensorValue={potValue} setSensorValue={setPotValue}
                        isFetching={isFetching} setIsFetching={setIsFetching} />
                </div>
                <div className="row m-1 ps-2 pe-2">
                    <SensorUnit name="Switch" disabled={props.automaticMode} isLoading={isLoading[2]}
                        setIsLoading={setIsLoading} sensorValue={switchValue} setSensorValue={setSwitchValue}
                        isFetching={isFetching} setIsFetching={setIsFetching} />
                </div>
            </div>
        </div>
    )
}

export default SensorDashboard