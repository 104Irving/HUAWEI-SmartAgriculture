export interface TabItem {
  icon:Resource;//图标
  icon_selected: Resource;
  title: string;//标题
  id: number;
}

export enum TabID {
  HOME,
  WATER_PLAN,
  MINE
}

export const TabItemList: TabItem[] = [
  {
    icon:$r('app.media.home0'),
    icon_selected: $r('app.media.home1'),
    title: '主页',
    id:TabID.HOME

  },
  {
    icon:$r('app.media.water0'),
    icon_selected: $r('app.media.water1'),
    title: '灌溉计划',
    id:TabID.WATER_PLAN

  },
  {
    icon:$r('app.media.user0'),
    icon_selected: $r('app.media.user1'),
    title: '我的',
    id:TabID.MINE

  }

]