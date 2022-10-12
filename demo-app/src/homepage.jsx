import React from "react";
import SensorDashboard from "./sensorValues";
import Settings from "./settings";
import logo from "./nait.jpg";
import { useState } from "react";

const Homepage = (props) => {
  const [automaticMode, setAutomaticMode] = useState(false);

  return (
    <>
      <div className='p-2 m-2 fs-4'>
        <div className='col m-2'>
          <div className='demo-title row m-2 ps-2 pe-2 fs-1'>
            <div className='col col-1'>
              <img className='logo' src={logo} alt='logo'></img>
            </div>
            <div className='col'>DEMO BOARD</div>
          </div>
          <div className='row m-2'>
            <div className='col m-2'>
              <div className='row m-1'>
                <h3 className='text-center'>SETTINGS</h3>
              </div>
              <div className='row m-1'>
                <Settings
                  automaticMode={automaticMode}
                  setAutomaticMode={setAutomaticMode}
                />
              </div>
            </div>
            <div className='col m-2 flx-grow-1'>
              <div className='row m-1'>
                <h3 className='text-center'>SENSORS</h3>
              </div>
              <div className='row m-1'>
                <SensorDashboard automaticMode={automaticMode} />
              </div>
            </div>
          </div>
        </div>
      </div>
      <p>TODO:</p>
      <li>Allow enable/disable automatic data retreival</li>
      <li>Allow specify time of automatic data retrieval</li>
      <li>With the timer value, pass to SensorDashboard</li>
      <li>
        From sensor dashboard, call api, get values of all sensor, send each
        value as a property to each unit
      </li>
      <li>Add instructions</li>
    </>
  );
};

export default Homepage;
