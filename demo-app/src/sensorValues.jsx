import React from "react";
import SensorUnit from "./sensorUnit";

const SensorDashboard = (props) => {

    return (
       <div className="d-flex">
            <div className="dashboard col p-1 position-relative">
                <div className="row m-1 ps-2 pe-2">
                    <SensorUnit name="Gyroscope" disabled={props.automaticMode}/>
                </div>
                <div className="row m-1 ps-2 pe-2">
                    <SensorUnit name="Potentiometer" disabled={props.automaticMode}/>
                </div>
                <div className="row m-1 ps-2 pe-2">
                    <SensorUnit name="Switch" disabled={props.automaticMode}/>
                </div>
            </div>
       </div>
)}

export default SensorDashboard