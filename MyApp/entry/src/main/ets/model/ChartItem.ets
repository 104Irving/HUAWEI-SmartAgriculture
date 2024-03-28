export interface ChartItem{
  ItemName:string
  //需要变量的数据表,需要联网获得
  Image:any
}

export const ChartItemList: ChartItem[] = [
  {
    ItemName:'温度',
    Image: $r("app.media.temperature")
  },
  {
    ItemName:'空气湿度',
    Image:$r("app.media.SoilHumidity")
  },
  {
    ItemName:'土壤湿度',
    Image:$r("app.media.SoilHumidity")
  },
  {
    ItemName:'光照',
    Image:$r("app.media.Lumination")
  },
  {
    ItemName:'二氧化碳浓度',
    Image:$r("app.media.co2")
  }
]