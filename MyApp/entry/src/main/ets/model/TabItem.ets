//Tab格式
export interface TabItem {
  icon:Resource;//图标
  icon_selected: Resource;
  title: string;//标题
  id: number;
}


//主界面tab转换列表
export enum MainTabID {
  HOME,
  MINE
}

export const MainTabItemList: TabItem[] = [
  {
    icon:$r('app.media.home0'),
    icon_selected: $r('app.media.home1'),
    title: '主页',
    id:MainTabID.HOME

  },
  {
  icon:$r('app.media.user0'),
  icon_selected: $r('app.media.user1'),
  title: '我的',
  id:MainTabID.MINE },
]


//主页农田室内室外转换tab
export enum FarmTabID {
  INDOOR,
  OUTDOOR
}

export const FarmIOTabList: TabItem[] = [
  {
    icon:$r('app.media.InDoor'),
    icon_selected: $r('app.media.InDoor'),
    title: '室内农田',
    id:FarmTabID.INDOOR
  },
  {
    icon:$r('app.media.OutDoor'),
    icon_selected: $r('app.media.OutDoor'),
    title: '室外农田',
    id:FarmTabID.OUTDOOR
  }
]

//管理农田参数转换Tab
export enum InDoorTabId {
  WaterPump,//水泵
  Ventilate,//通风
  LightSub,//补光
}

export const InDoorTabList: TabItem[] = [
  {
    icon:$r('app.media.WaterPump'),
    icon_selected: $r('app.media.WaterPump'),
    title: '水泵',
    id:InDoorTabId.WaterPump
  },
  {
    icon:$r('app.media.Ventilate'),
    icon_selected: $r('app.media.Ventilate'),
    title: '通风',
    id:InDoorTabId.Ventilate
  },
  {
    icon:$r('app.media.LightSub'),
    icon_selected: $r('app.media.LightSub'),
    title: '补光',
    id:InDoorTabId.LightSub
  }
]