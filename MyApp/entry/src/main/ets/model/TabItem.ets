export interface TabItem {
  icon:Resource;//图标
  icon_selected: Resource;
  title: string;//标题
  id: number;
}

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