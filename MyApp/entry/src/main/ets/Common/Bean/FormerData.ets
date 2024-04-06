export class FormerData{
  Temperature: number[]  //温度
  Humidity: number[]     //空气湿度
  SoilHumidity: number[] //土壤湿度
  Lumination: number[]   //光照
  co2: number[]          //二氧化碳浓度

  setVal(Tem:number[], Hum:number[], Soi:number[], Lum:number[], CO2:number[] ){
    this.Temperature = Tem
    this.Humidity = Hum
    this.SoilHumidity = Soi
    this.Lumination = Lum
    this.co2 = CO2
  }
}