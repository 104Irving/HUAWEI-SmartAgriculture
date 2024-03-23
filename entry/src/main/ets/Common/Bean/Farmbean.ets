export default class FarmBean {
  fieldId: number;//农田ID
  name: string ;//农田名
  temperature: number;//温度
  humidity: number;//空气湿度
  co2: number;//二氧化碳浓度
  lumination: number;//光照强度
  soilHumidity: number;//土壤湿度

  //相当于是初始化函数
  constructor(fieldId: number,
              name: string,
              temperature: number,
              humidity:number,
              co2: number,
              lumination: number,
              soilHumidity: number)
  {
    this.fieldId = fieldId;
    // this.fieldIndv = fieldIndv;
    this.name = name;
    this.temperature = temperature;
    this.humidity = humidity;
    this.co2 = co2;
    this.lumination = lumination;
    this.soilHumidity = soilHumidity
  }
}


