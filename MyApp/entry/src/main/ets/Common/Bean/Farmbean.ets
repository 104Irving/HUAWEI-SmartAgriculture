export default class FarmBean {
  fieldID: number;//农田ID
  name: string ;//农田名
  temperature: number;//温度
  humidity: number;//空气湿度
  co2: number;//二氧化碳浓度
  lumination: number;//光照强度
  soilHumidity: number;//土壤湿度
  If_show:boolean = false //

  //相当于是初始化函数
  constructor(fieldId: number,
              name: string,
              temperature: number,
              humidity:number,
              co2: number,
              lumination: number,
              soilHumidity: number,
              ifShow: boolean)
  {
    this.fieldID = fieldId;
    this.name = name;
    this.temperature = temperature;
    this.humidity = humidity;
    this.co2 = co2;
    this.lumination = lumination;
    this.soilHumidity = soilHumidity
    this.If_show = ifShow
  }

}


