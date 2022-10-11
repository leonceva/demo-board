import React from "react";

const Settings = (props) => {

    return (
        <div className="d-flex flex-row justify-content-evenly">
            <h4>
                Instructions
            </h4>
            <div className="dashboard p-1">
                <div className="d-flex flex-row pt-2 pb-3 justify-content-around">
                    <h4 className={`ps-2 pe-2 ` + (!props.automaticMode? `mode-selected`: `mode-unselected`)}>Manual</h4>
                    <div className="ps-2 pe-2">
                        <div class="form-check form-switch">
                            <input onChange={()=>{props.setAutomaticMode(!props.automaticMode)}} class="form-check-input" type="checkbox" id="flexSwitchCheckDefault"/>
                        </div>
                    </div>
                    <h4 className={`ps-2 pe-2 ` + (props.automaticMode? `mode-selected`: `mode-unselected`)}>Automatic</h4>
                </div>
                {props.automaticMode &&
                <h5 className="row pt-3 pb-2" style={{ justifyContent: 'center' }}>
                    Automatic Mode Timer
                </h5>}
            </div>
        </div>
    )
}

export default Settings