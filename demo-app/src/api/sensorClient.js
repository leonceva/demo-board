import axios from "axios";

const SENSOR_CONTROLLER_BASE_URL = `http://localhost:3005`

export const getGyroData = async () => {
    return await axios.get(`${SENSOR_CONTROLLER_BASE_URL}/gyro`, {crossDomain: true})
}

export const getPotData = async () => {
    return await axios.get(`${SENSOR_CONTROLLER_BASE_URL}/pot`)
}

export const getSwitchData = async () => {
    return await axios.get(`${SENSOR_CONTROLLER_BASE_URL}/switch`)
}

export const getAllData = async () => {
    return await axios.get(`${SENSOR_CONTROLLER_BASE_URL}/all`)
}