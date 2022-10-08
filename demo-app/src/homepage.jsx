import React from "react"
import SensorDashboard from "./sensorValues"
import Settings from "./settings"

const Homepage = (props) => {


    return (
        <>
            <div className="d-flex p-2 m-2 fs-4">
                <div className="col m-2">
                    <div className="demo-title row m-2 ps-2 pe-2 fs-1 d-inline-flex">
                        DEMO BOARD
                    </div>
                    <div className="row m-2">
                        <div className="col m-2">
                            <div className="row m-1">
                                <p className="text-center">
                                    SETTINGS
                                </p>
                            </div>
                            <div className="row m-1">
                                <Settings/>
                            </div>
                        </div>
                        <div className="col m-2 flx-grow-1">
                            <div className="row m-1">
                                <p className="text-center">
                                    Sensors
                                </p>
                            </div>
                            <div className="row m-1">
                                <SensorDashboard/>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <p>TODO:</p>
            <ul>Settings dashboard</ul>
            <ul>Allow enable/disable automatic data retreival</ul>
            <ul>Allow specify time of automatic data retrieval</ul>
            <ul>Disable Sensor buttons while in automatic mode</ul>
            <ul>In manual mode, button press to retrieve specific sensor data with loader</ul>
        </>
    )
}

export default Homepage