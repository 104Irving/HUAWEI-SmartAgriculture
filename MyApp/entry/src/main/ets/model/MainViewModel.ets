import FarmBean from '../common/bean/FarmBean';

//目前是随机变动
export class MainViewModel {

  //土壤传感器数据更新函数
  public getFarmData(fieldId: number, temperature:number,
                     humidity:number, lumination:number,
                     co2:number, soilHumidity):FarmBean {

    let farmBean = new FarmBean(1,'老张的玉米地',22.5,56,30,800,25);
    //温度
    farmBean.temperature = temperature

    //空气湿度
    farmBean.humidity = humidity

    //光照
    farmBean.lumination = lumination

    //二氧化碳浓度
    farmBean.co2 = co2

    //土壤湿度
    farmBean.soilHumidity = soilHumidity
    return farmBean;
  }
}

export default new MainViewModel();


