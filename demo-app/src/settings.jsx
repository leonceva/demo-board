import React, { useState } from "react";
import AutomaticModeRange from "./automaticModeRange";
import AutomaticModeProgress from "./automaticModeProgress";
import Button from "react-bootstrap/Button"

const Settings = (props) => {

	const [buttonStart, setButtonStart] = useState(true)

	return (
		<div className='d-flex flex-row justify-content-evenly settings'>
			<div className="dashboard" style={{ maxWidth: "450px" }}>
				<h4 className='pe-3 pt-2'>Instructions</h4>
				<div className="ms-3 me-3 text-start fs-5">
					{props.automaticMode ?
						<p>
							Use the slider to set the time interval automatic data retrieval.
							While the automatic mode is active, all sensor data will be gathered,
							and the individual sensor buttons are disabled.
							Stop the sequence to change the time interval.
						</p>
						: <p>
							Click each sensor button to gather its data. <br></br>
							The user should refrain from rapid subsequent clicks, as this will cause
							increased wireless data traffic. <br></br>
							A few seconds between clicks is recommended.
						</p>

					}
				</div>
			</div>
			<div className='dashboard p-1'>
				<div className='d-flex flex-row pt-2 pb-3 justify-content-around'>
					<h4
						className={
							`ps-2 pe-2 ` +
							(!props.automaticMode ? `mode-selected` : `mode-unselected`)
						}
					>
						Manual
					</h4>
					<div className='ps-2 pe-2'>
						<div className='form-check form-switch settings-button'>
							<input
								onChange={() => {
									props.setAutomaticMode(!props.automaticMode);
								}}
								className='form-check-input'
								type='checkbox'
								id='flexSwitchCheckDefault'
							/>
						</div>
					</div>
					<h4
						className={
							`ps-2 pe-2 ` +
							(props.automaticMode ? `mode-selected` : `mode-unselected`)
						}
					>
						Automatic
					</h4>
				</div>
				{props.automaticMode && (
					<div className="col flex-column">
						<h5 className='row pt-3 pb-2' style={{ justifyContent: "center" }}>
							{`Automatic Mode Timer: ${props.timerValue}s`}
						</h5>
						<div className="row">
							<AutomaticModeRange disabled={!buttonStart} timerValue={props.timerValue} setTimerValue={props.setTimerValue} />
						</div>
						<div className="row center"
							style={{ paddingLeft: "25%", paddingRight: "25%", paddingBottom: "2%" }}>
							{!buttonStart ?
								<Button variant="danger" onClick={() => {
									props.setIsRunning(false)
									setButtonStart(!buttonStart)
								}}>STOP</Button>
								: <Button variant="success" onClick={() => {
									props.setIsRunning(true)
									setButtonStart(!buttonStart)
								}}>START</Button>

							}
						</div>
						{props.isRunning &&
							<div className="row" style={{ justifyContent: "center", paddingBottom: "2%", paddingTop: "2%" }}>
								<AutomaticModeProgress active={props.isRunning} timerValue={props.timerValue} setPingSensors={props.setPingSensors} isRunning={props.isRunning} setIsRunning={props.setIsRunning} />
							</div>}
					</div>
				)}
			</div>
		</div>
	);
};

export default Settings;